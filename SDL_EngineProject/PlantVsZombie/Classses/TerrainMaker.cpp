#include "TerrainMaker.h"
#include "StaticData.h"

TerrainMaker::TerrainMaker()
	:m_callback(nullptr)
{
}

void TerrainMaker::startParse(TMXTiledMap*tiledMap,const function<void (Terrain*)>& callback)
{
	/*������ʹ�õ��ַ������Ƕ�����*/
	//��ֵ
	m_callback = callback;
	//��ȡ�õ�ͼ����
	auto &properties = tiledMap->getProperties();
	//��ȡ���ͣ������;����Ӻδ��������ɵ���
	auto type = properties.at("type").asString();
	//��ͼ�����з���
	if (type == "tile layer")
	{
		//��ȡ��Ӧ��ͼ���
		auto layer = dynamic_cast<TMXLayer*>(tiledMap->getLayer("terrain tile layer"));
		//��ʼ����
		this->parseTileLayer(layer,tiledMap);
	}
	//����ʵ���
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
		//��ȡid
		auto gid = atoi(child->getName().c_str());
		//��ȡ����
		auto valueMap = tiledMap->getTilePropertiesForGID(gid);
		//��ȡ terrain type
		auto sTerrainType = valueMap.at("terrain type").asString();
		//��������ת��
		auto terrainType = StaticData::convertStrToTerrainType(sTerrainType);

		Terrain*terrain = Terrain::create();
		terrain->setTerrainType(terrainType);
		terrain->setDestroyed(false);
		terrain->setPosition(child->getPosition());
		terrain->setContentSize(child->getContentSize());
		//�����ص�
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
		//���ݲ�ͬ�����ʹ������ֵ���
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
		//�����ص�
		m_callback(terrain);
	}
}
