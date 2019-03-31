#include "LevelLayer.h"
#include "TerrainMaker.h"
#include "Terrain.h"
#include "Plant.h"
#include "Carrier.h"
#include "VesselPlant.h"
#include "Defender.h"

LevelLayer::LevelLayer()
	:m_pTiledMap(nullptr),m_bProduceSun(false)
	,m_elapsed(0.f),m_pDelegate(nullptr)
	,m_nInitialSun(0),m_levelCardType(LevelCardType::Plant)
	,m_curActiveTime(ActiveTime::Day)
{
}

LevelLayer::~LevelLayer()
{
	for (auto it = m_zombiePathVec.begin();it != m_zombiePathVec.end();)
	{
		auto zombiePath = *it;

		delete zombiePath;
		it = m_zombiePathVec.erase(it);
	}
}

LevelLayer*LevelLayer::create(const string&sLevel)
{
	auto layer = new LevelLayer();

	if (layer && layer->initWithLevel(sLevel))
		layer->autorelease();
	else
		SDL_SAFE_DELETE(layer);

	return layer;
}

bool LevelLayer::initWithLevel(const string&sLevel)
{
	//加载关卡
	m_pTiledMap = TMXTiledMap::create(sLevel);
	this->addChild(m_pTiledMap);
	//读取有用的属性
	this->setAnchorPoint(Point::ZERO);
	this->loadProperties();
	this->loadZombiePath();
	//设置尺寸
	auto size = m_pTiledMap->getLayer<TMXImageLayer*>("bg")->getContentSize();
	this->setContentSize(size);
	//获取地形
	TerrainMaker maker;
	maker.startParse(m_pTiledMap,SDL_CALLBACK_1(LevelLayer::makeTerrainCallback,this));
	//塔基加载完成
	for (auto it = m_terrains.begin();it != m_terrains.end();it++)
	{
		auto & terrains = it->second;

		sort(terrains.begin(),terrains.end(),terrainComparisonLess);
	}

	return true;
}

void LevelLayer::update(float dt)
{
	if (!m_bProduceSun)
		return ;
	m_elapsed += dt;
	//产生阳光
	if (m_elapsed >= 16.f)
	{
		m_elapsed -= 16.f;

		Size visibleSize = Director::getInstance()->getVisibleSize();
		Point bornPos = Point(visibleSize.width/2,0);
		float duration = 6.f;
		MoveBy*move = MoveBy::create(duration,Point(0,500.f));

		m_pDelegate->makeSun(25,move,bornPos);
	}
}

TMXTiledMap* LevelLayer::getTiledMap()const
{
	return m_pTiledMap;
}

TMXLayer*LevelLayer::getEntityLayer()
{
	auto layer = m_pTiledMap->getLayer<TMXLayer*>("entity layer");
	return layer;
}

Terrain*LevelLayer::getClickedTerrain(const Point&nodePos)
{
	for (auto mapIter = m_terrains.begin();mapIter != m_terrains.end();mapIter++)
	{
		auto terrainVec = mapIter->second;

		for (auto it = terrainVec.begin();it != terrainVec.end();it++)
		{
			auto terrain = *it;
			auto rect = terrain->getBoundingBox();

			if (rect.containsPoint(nodePos))
				return terrain;
		}
	}
	return nullptr;
}

vector<Terrain*>& LevelLayer::getTerrainsOfRow(int row)
{
	auto&terrains = m_terrains.at(row);

	return terrains;
}

void LevelLayer::setDelegate(LevelLayerDelegate*pDelegate)
{
	m_pDelegate = pDelegate;
}

Plant* LevelLayer::getTopPlant(Carrier*carrier)
{
	auto innerPlant = carrier->getInnerPlant();
	//内部植物为容器植物
	if (innerPlant != nullptr
		&& innerPlant->getPlantType() == PlantType::Vessel)
	{
		auto vessel = static_cast<VesselPlant*>(innerPlant)->getInnerCarrier();
		//容器内还存在植物
		if (vessel->getInnerPlant() != nullptr)
			return vessel->getInnerPlant();

	}
	return innerPlant;
}

Plant*LevelLayer::getTopPlantOfRemoval(Carrier*carrier)
{
	auto innerPlant = carrier->getInnerPlant();
	Plant *target = innerPlant;
	//内部植物存在并且为容器植物
	if (innerPlant != nullptr 
		&& innerPlant->getPlantType() == PlantType::Vessel)
	{
		auto vesselPlant = static_cast<VesselPlant*>(innerPlant);
		auto vessel = vesselPlant->getInnerCarrier();
		//容器植物中存在植物，则返回
		if (vessel->getInnerPlant() != nullptr)
		{
			target = vessel->getInnerPlant();
		}
		//容器植物存在保卫者，返回
		else if (vessel->getDefender() != nullptr)
		{
			target = vessel->getDefender();
		}
	}
	//载体中有保卫者，返回该defender
	else if (carrier->getDefender() != nullptr)
	{
		target = carrier->getDefender();
	}
	return target;
}

Plant* LevelLayer::getTopPlantOfAttack(Carrier*carrier)
{
	auto innerPlant = carrier->getInnerPlant();

	if (carrier->getDefender() != nullptr)
		return carrier->getDefender();
	else if (innerPlant != nullptr
		&& innerPlant->getPlantType() == PlantType::Vessel)
	{
		auto innerCarrier = static_cast<VesselPlant*>(innerPlant)->getInnerCarrier();

		if (innerCarrier->getDefender() != nullptr)
			return innerCarrier->getDefender();
		else if (innerCarrier->getInnerPlant() != nullptr)
			return innerCarrier->getInnerPlant();
	}
	else
		return innerPlant;

	return nullptr;
}

Carrier*LevelLayer::getVesselOfPlant(Carrier*carrier,Plant*plant)
{
	auto innerPlant = carrier->getInnerPlant();

	while (innerPlant != nullptr 
		&& innerPlant->getPlantType() == PlantType::Vessel)
	{
		auto vesselPlant = static_cast<VesselPlant*>(innerPlant);
		auto vessel = vesselPlant->getInnerCarrier();
		//容器中存在对应的植物
		if (vessel->getInnerPlant() == plant)
		{
			return vessel;
		}
		else
		{
			innerPlant = vessel->getInnerPlant();
		}
	}
	return carrier;
}

int LevelLayer::getSumOfZOrderPlant(Terrain*terrain,Plant*plant)
{
	int tag = 0;
/*	Carrier*carrier = terrain;

	do
	{
		tag += carrier->getRow();
		auto innerPlant = carrier->getInnerPlant();

		if (plant == innerPlant)
			break;
		else if (innerPlant->getPlantType() == PlantType::Vessel)
		{
			carrier = static_cast<VesselPlant*>(innerPlant)->getInnerCarrier();
		}
		else
			break;

	}while(carrier != nullptr);*/
	if (plant->getPlantType() == PlantType::Defender)
		tag = 3;
	else if (plant->getPlantType() == PlantType::Vessel)
		tag = 1;
	else
		tag = 2;

	return tag;
}

ValueVector LevelLayer::getEntityObjects()
{
	auto entityObjectLayer = m_pTiledMap->getObjectGroup("entity object layer");
	auto groups = entityObjectLayer->getObjects();

	return groups;
}

vector<ZombiePath*>& LevelLayer::getZombiePaths()
{
	return m_zombiePathVec;
}

ZombiePath*LevelLayer::getZombiePathOfRow(int row)
{
	ZombiePath* zombiePath = nullptr;

	for (const auto&path : m_zombiePathVec)
	{
		if (path->row == row)
		{
			zombiePath = path;
			break;
		}
	}

	return zombiePath;
}

LevelCardType LevelLayer::getLevelCardShowType()const
{
	return m_levelCardType;
}

ActiveTime LevelLayer::getCurActiveTime()const
{
	return m_curActiveTime;
}

void LevelLayer::makeTerrainCallback(Terrain*terrain)
{
	//检测该地形在第几行
	auto rect = terrain->getBoundingBox();

	for (auto zombiePath : m_zombiePathVec)
	{
		const auto& points = zombiePath->points;
		auto row = zombiePath->row;

		for (unsigned int i = 0;i < points.size() - 1;i++)
		{
			auto pos1 = points.at(i);
			auto pos2 = points.at(i + 1);

			if (rect.intersectLine(pos1,pos2))
			{
				terrain->setRow(row);
				m_terrains[row].push_back(terrain);
				//添加到实体层
				auto layer = this->getEntityLayer();
				layer->addChild(terrain);
			}
		}
	}
}

void LevelLayer::loadProperties()
{
	auto &properties = m_pTiledMap->getProperties();

	for (auto property : properties)
	{
		string name = property.first;
		if (name == "produce sun")
		{
			m_bProduceSun = property.second.asBool();
		}
		else if (name == "initial sun")
		{
			m_nInitialSun = property.second.asInt();
		}
		else if (name == "card")
		{
			auto type = property.second.asString();

			if (type == "plant")
				m_levelCardType = LevelCardType::Plant;
			else if (type == "zombie")
				m_levelCardType = LevelCardType::Zombie;
		}
		else if (name == "time")
		{
			auto type = property.second.asString();

			if (type == "day")
				m_curActiveTime = ActiveTime::Day;
			else if (type == "night")
				m_curActiveTime = ActiveTime::Night;
		}
	}
}

void LevelLayer::loadZombiePath()
{
	auto groupGroup = m_pTiledMap->getObjectGroup("zombie path");
	auto &objects = groupGroup->getObjects();

	for (const auto& object : objects)
	{
		ZombiePath*zombiePath = new ZombiePath();
		const auto &dict = object.asValueMap();

		auto x = dict.at("x").asInt();
		auto y = dict.at("y").asInt();
		auto properties = dict.at("properties").asValueMap();
		auto points = dict.at("polyline").asValueVector();

		for (const auto& dict : points)
		{
			const auto&point = dict.asValueMap();

			float realX = float(x + point.at("x").asInt());
			float realY = float(y + point.at("y").asInt());

			zombiePath->points.push_back(Point(realX,realY));
		}
		zombiePath->row = properties.at("row").asInt();

		m_zombiePathVec.push_back(zombiePath);
	}
}

bool LevelLayer::terrainComparisonLess(Terrain* n1, Terrain* n2)
{
	return n1->getPositionX() < n2->getPositionX();
}