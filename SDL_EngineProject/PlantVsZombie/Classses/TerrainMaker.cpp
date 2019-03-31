#include "TerrainMaker.h"
#include "StaticData.h"

TerrainMaker::TerrainMaker()
	:m_callback(nullptr)
{
}

void TerrainMaker::startParse(TMXTiledMap*tiledMap,const function<void (Terrain*)>& callback)
{
	/*这里面使用的字符串都是定死的*/
	//赋值
	m_callback = callback;
	//获取该地图属性
	auto &properties = tiledMap->getProperties();
	//获取类型，该类型决定从何处解析生成地形
	auto type = properties.at("type").asString();
	//从图块层进行分析
	if (type == "tile layer")
	{
		//获取对应的图块层
		auto layer = dynamic_cast<TMXLayer*>(tiledMap->getLayer("terrain tile layer"));
		//开始解析
		this->parseTileLayer(layer,tiledMap);
	}
	//解析实体层
	else if (type == "object layer")
	{
		auto objectGroup = tiledMap->getObjectGroup("terrain object layer");
		this->parseObjectGroup(objectGroup);
	}
}

void TerrainMaker::parseTileLayer(TMXLayer*layer,TMXTiledMap*tiledMap)
{
	auto children = layer->getChildren();

	for (auto child : children)
	{
		//获取id
		auto gid = atoi(child->getName().c_str());
		//获取属性
		auto valueMap = tiledMap->getTilePropertiesForGID(gid);
		//获取 terrain type
		auto sTerrainType = valueMap.at("terrain type").asString();
		//进行类型转换
		auto terrainType = StaticData::convertStrToTerrainType(sTerrainType);

		Terrain*terrain = Terrain::create();
		terrain->setTerrainType(terrainType);
		terrain->setDestroyed(false);
		terrain->setPosition(child->getPosition());
		terrain->setContentSize(child->getContentSize());
		//函数回调
		m_callback(terrain);
	}
}

void TerrainMaker::parseObjectGroup(TMXObjectGroup*objectGroup)
{
	auto&groups = objectGroup->getObjects();

	for (const auto& object:groups)
	{
		const auto &dict = object.asValueMap();

		auto properties = dict.at("properties").asValueMap();
		auto sType = properties.at("terrain type").asString();

		auto type = StaticData::convertStrToTerrainType(sType);
		//根据不同的类型创建各种地形
		Terrain*terrain = nullptr;
		//TODO
		if (type == TerrainType::Lawn)
			terrain = Lawn::create();
		else
			terrain = Terrain::create();

		terrain->setTerrainType(type);
		terrain->setDestroyed(false);

		int x = dict.at("x").asInt();
		int y = dict.at("y").asInt();
		int width = dict.at("width").asInt();
		int height = dict.at("height").asInt();

		terrain->setPosition(Point(x + width/2.f,y + height/2.f));
		terrain->setContentSize(Size((float)width,(float)height));
		//函数回调
		m_callback(terrain);
	}
}
