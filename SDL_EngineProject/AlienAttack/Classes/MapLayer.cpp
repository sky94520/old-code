#include "MapLayer.h"
#include "Player.h"

MapLayer::MapLayer()
	:m_pTiledMap(nullptr),m_pBg1(nullptr)
	,m_pBg2(nullptr),m_scrollSpeed(0.f)
{
}
MapLayer::~MapLayer()
{
}
MapLayer*MapLayer::create(const string&level)
{
	auto layer = new MapLayer();
	if(layer &&layer->init(level))
		layer->autoRelease();
	else
		SDL_SAFE_DELETE(layer);
	return layer;
}
bool MapLayer::init(const string&level)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	m_pTiledMap = TMXTiledMap::create(level);
	this->addChild(m_pTiledMap);
	//获取背景属性并设置
	auto clouds = m_pTiledMap->getPropertyForName("clouds").asString();

	m_pBg1 = Sprite::create(clouds);
	m_pBg2 = Sprite::create(clouds);
	Size bgSize = m_pBg1->getContentSize();

	m_pBg1->setAnchorPoint(Point(0.f,0.f));
	m_pBg1->setScale(visibleSize.width/bgSize.width,visibleSize.height/bgSize.height);
	m_pBg2->setAnchorPoint(Point(0.f,0.f));
	m_pBg2->setScale(visibleSize.width/bgSize.width,visibleSize.height/bgSize.height);
	m_pBg2->setPosition(visibleSize.width,0);

	this->addChild(m_pBg1,-1);
	this->addChild(m_pBg2,-1);

	m_scrollSpeed = 1.f;

	return true;
}
void MapLayer::update(float dt)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	Size tileSize = m_pTiledMap->getTileSize();
	Size mapSize = m_pTiledMap->getMapSize();
	//获取地图总长度
	Size size = Size(mapSize.width*tileSize.width,mapSize.height*tileSize.height);
	//获取当前位置
	Point curPos = m_pTiledMap->getPosition();

	if(curPos.x > visibleSize.width - size.width)
	{
		//地图移动
		m_pTiledMap->setPositionX(curPos.x - m_scrollSpeed);

		auto x1 = m_pBg1->getPositionX() - m_scrollSpeed;
		auto x2 = m_pBg2->getPositionX() - m_scrollSpeed;
		//背景移动
		if(x1 <= -visibleSize.width)
			x1 = visibleSize.width;
		if(x2 <= -visibleSize.width)
			x2 = visibleSize.width;
		m_pBg1->setPositionX(x1);
		m_pBg2->setPositionX(x2);
	}
	else
		m_scrollSpeed = 0.f;
}
void MapLayer::checkCollisionBetweenPlayerAndMap(Player*player)
{
	//获取碰撞层
	auto layer = m_pTiledMap->getLayer("Collision");
	//获取当前地图位置
	Point mapPosX = abs(m_pTiledMap->getPositionX());
	Size tileSize = m_pTiledMap->getTileSize();
	Rect r = player->getBoundingBox();
	r.origin += mapPosX;
	
	int x = r.origin.x/tileSize.width;
	int y = r.origin.y/tileSize.height;
	int w = r.size.width/tileSize.width;
	int h = r.size.height/tileSize.height;
	for(int i=0;i <= w;i++)
	{
		for(int j=0;j <= h;j++)
		{
			int gid = layer->getTileGIDAt(Point(x+i,y+j));
			if(gid != 0)
			{
				player->hurt(100);
				return ;
			}
		}
	}
}
std::vector<TMXObject*> MapLayer::getTMXObjects()
{
	std::vector<TMXObjectGroup*>& objectGroups = m_pTiledMap->getObjectGroups();
	std::vector<TMXObject*> objects;
	for(auto group:objectGroups)
	{
		auto objectTMX = group->getObjects();
		for(auto object:objectTMX)
			objects.push_back(object);
	}
	return objects;
}
void MapLayer::reset()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	m_pBg1->setPosition(Point::ZERO);
	m_pBg2->setPosition(visibleSize.width,0);

	m_pTiledMap->setPosition(Point::ZERO);
}
void MapLayer::clear()
{
	m_pTiledMap->removeFromParent();
	m_pBg1->removeFromParent();
	m_pBg2->removeFromParent();
}