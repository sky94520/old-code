#include "SeedLayer.h"
#include "Seed.h"
#include "PlantFactory.h"
#include "SunFlower.h"
#include "Peashooter.h"
#include "WallNut.h"
#include "CherryBomb.h"
#include "PotatoMine.h"
SeedLayer::SeedLayer():m_selectedIndex(-1),m_pSelectedHigh(nullptr)
{
}
SeedLayer::~SeedLayer()
{
	PlantFactory::getInstance()->purge();
}
bool SeedLayer::init()
{
	//根据name 来加载植物工厂
	PlantFactory::getInstance()->registerType("SunFlower",new SunFlowerCreator());
	PlantFactory::getInstance()->registerType("Peashooter",new PeashooterCreator());
	PlantFactory::getInstance()->registerType("WallNut",new WallNutCreator());
	PlantFactory::getInstance()->registerType("CherryBomb",new CherryBombCreator());
	PlantFactory::getInstance()->registerType("PotatoMine",new PotatoMineCreator());

	m_pSelectedHigh = Sprite::create("Resources/Card/ClickHigh.png");
	m_pSelectedHigh->setVisible(false);
	this->addChild(m_pSelectedHigh,4);
	//在这里读取配置文件
	return true;
}
void SeedLayer::update(float dt)
{
	for(int i=0;i < m_seeds.size();i++)
	{
		auto seed = m_seeds.at(i);
		seed->update(dt);
	}
}
bool SeedLayer::addSeed(const std::string &name)
{
	//查看总种子包来确定位置
	auto size = m_seeds.size();
	//以后通过配置文件创建Seed
	Seed*seed = Seed::create(name);
	seed->setPositionY(seed->getContentSize().height * size);
	this->addChild(seed);
	m_seeds.push_back(seed);
	return true;
}
void SeedLayer::removeSeed(const std::string &type)
{
	//留待以后扩展
}
Seed* SeedLayer::getSelectedSeed()
{
	if(m_selectedIndex>=0 && m_selectedIndex < m_seeds.size())
	{
		return m_seeds.at(m_selectedIndex);
	}
	return nullptr;
}
void SeedLayer::clearClickHigh()
{
	m_pSelectedHigh->setVisible(false);
	m_selectedIndex = -1;
}
bool SeedLayer::setSelectedSeed(const Point&point)
{
	Seed* seed = nullptr;
	unsigned int index = 0;
	for(int i=0;i<m_seeds.size();i++)
	{
		Rect rect = m_seeds.at(i)->getBoundingBox();
		rect.origin = m_seeds.at(i)->getWorldPosition();
		//如果不在cd中
		if(m_seeds.at(i)->canClicked() && rect.containsPoint(point))
		{
			seed = m_seeds.at(i);
			index = i;
			break;
		}
	}
	//赋值
	if(seed)
	{
		//如果当前种子包已选中，则取消选中
		if(index == m_selectedIndex)
		{
			m_selectedIndex = -1;
			m_pSelectedHigh->setVisible(false);
			return true;
		}
		else//选中该种子包
		{
			m_selectedIndex = index;
			m_pSelectedHigh->setPosition(seed->getPosition());
			m_pSelectedHigh->setVisible(true);
			return true;
		}
	}
	return false;
}
Seed* SeedLayer::getItemForTouch(Touch*touch)
{
	auto point = touch->getLocation();
	for(auto seed:m_seeds)
	{
		Rect rect = seed->getBoundingBox();
		rect.origin = seed->getWorldPosition();
		if(rect.containsPoint(point))
			return seed;
	}
	return nullptr;
}