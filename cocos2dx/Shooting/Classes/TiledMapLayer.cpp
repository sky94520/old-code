#include "TiledMapLayer.h"
TiledMapLayer::TiledMapLayer()
	:m_pTiledMap(nullptr)
{
}
TiledMapLayer::~TiledMapLayer()
{
}
TiledMapLayer*TiledMapLayer::create(const std::string&tmx)
{
	auto tmxLayer = new TiledMapLayer();
	if(tmxLayer && tmxLayer->init(tmx))
		tmxLayer->autorelease();
	else
		CC_SAFE_DELETE(tmxLayer);
	return tmxLayer;
}
bool TiledMapLayer::init(const std::string&tmx)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//创建tmx
	m_pTiledMap = TMXTiledMap::create(tmx);
	m_pTiledMap->setAnchorPoint(ccp(0.5f,0.5f));
	m_pTiledMap->setPosition(ccp(visibleSize.width/2,visibleSize.height/2));
	this->addChild(m_pTiledMap);
	return true;
}
ValueMap TiledMapLayer::getObject(const std::string&name)const
{
	auto objects = m_pTiledMap->getObjectGroup("object");
	return objects->getObject(name);
}
TMXLayer*TiledMapLayer::getLayer(const std::string&name)const
{
	return m_pTiledMap->getLayer(name);
}
ValueMap TiledMapLayer::getValueMapByPosition(const std::string&name,const Point&pos)
{
	auto layer = m_pTiledMap->getLayer(name);
	//转换成tmx坐标
	auto tileCoord = tileCoordFromPosition(pos);
	//获得对应的GID
	int tileGID = layer->getTileGIDAt(tileCoord);
	if(tileGID > 0)
	{
		Value prop = m_pTiledMap->getPropertiesForGID(tileGID);
		ValueMap propValueMap = prop.asValueMap();
		//std::string value = propValueMap["name"].asString();
		return propValueMap;
	}
	return ValueMap();
}
Vec2 TiledMapLayer::tileCoordFromPosition(const Vec2&pos)
{
	int x = pos.x/m_pTiledMap->getTileSize().width;
	int y = ((m_pTiledMap->getMapSize().height*m_pTiledMap->getTileSize().height)-pos.y)
		/m_pTiledMap->getTileSize().height;
	return Vec2(x,y);
}