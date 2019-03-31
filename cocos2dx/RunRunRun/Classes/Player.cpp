#include "Player.h"
#include "WinScene.h"

bool Player::init()
{
	isJumping = false;
	return true;
}
void Player::run()
{
	SpriteFrameCache*frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("boys.plist","boys.png");

	SpriteFrame*frame = NULL;
	Vector<SpriteFrame*> frameList;
	//创建精灵帧对象，添加到列表中
	for(int i = 1;i <= 15;i++)
	{
		frame = frameCache->getSpriteFrameByName(StringUtils::format("run%d.png",i));
		frameList.pushBack(frame);
	}
	//根据精灵帧对象创建动画对象
	Animation*animation = Animation::createWithSpriteFrames(frameList);
	//一直循环
	animation->setLoops(-1);
	//每帧播放时间间隔
	animation->setDelayPerUnit(0.08f);
	//创建动作动画
	Animate*animate = Animate::create(animation);
	//精灵执行动作
	 m_sprite->runAction(animate);
	
}
void Player::setViewPointByPlayer()
{
	if(m_sprite == NULL)
		return ;
	Layer*parent = (Layer*)getParent();
	//地图方块数量
	Size mapTiledNum = m_map->getMapSize();
	//地图单个格子大小
	Size tiledSize = m_map->getTileSize();
	//map大小
	Size mapSize = Size(
	mapTiledNum.width * tiledSize.width,
		mapTiledNum.height * tiledSize.height);
	//屏幕大小
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//主角坐标
	Point spritePos = getPosition();
	//
	float x = std::max(spritePos.x,visibleSize.width/2);
	float y = std::max(spritePos.y,visibleSize.height/2);
	//
	x = std::min(x,mapSize.width - visibleSize.width/2);
	y = std::min(y,mapSize.height - visibleSize.height/2);

	Point destPos =Point(x,y);

	Point centerPos = Point(visibleSize.width/2,visibleSize.height/2);

	Point viewPos = centerPos - destPos;
	parent->setPosition(viewPos);
}
void Player::setTagPosition(int x,int y)
{
	//取主角前方的坐标
	Size spriteSize = m_sprite->getContentSize();
	Point dstPos = Point(x + spriteSize.width/2,y);
	//获取当前主角前方坐标在地图中德格子位置
	Point tiledPos = tileCoordForPosition(Point(dstPos.x,dstPos.y));
	//获取地图格子的唯一标识ID
	int tiledGid = meta->getTileGIDAt(tiledPos);

	if(tiledGid != 0)
	{
	Value properties = m_map->getPropertiesForGID(tiledGid);
	ValueMap propertiesMap = properties.asValueMap();

	if(propertiesMap.find("Collidable") != propertiesMap.end())
	{
		Value prop = propertiesMap.at("Collidable");

		if(prop.asString().compare("true") == 0 && isJumping == false)
		{
			isJumping = true;

			auto jumpBy = JumpBy::create(0.5f,Point(-100,0),80,1);
			CallFunc*callfunc = CallFunc::create([&](){
			isJumping = false;
			});

			auto actions = Sequence::create(jumpBy,callfunc,NULL);
			this->runAction(actions);
		}
	}

	if(propertiesMap.find("food") != propertiesMap.end())
	{
		Value prop = properties.asValueMap().at("food");
		if(prop.asString().compare("true") == 0)
		{
			TMXLayer*barrier = m_map->getLayer("barrier");
			barrier->removeTileAt(tiledPos);
		}
	}
	if(propertiesMap.find("win") != propertiesMap.end())
	{
		Value prop = properties.asValueMap().at("win");
		if(prop.asString().compare("true") == 0)
			Director::getInstance()->replaceScene(WinScene::createScene());
	}
}

	Entity::setTagPosition(x,y);

	setViewPointByPlayer();
}
void Player::setTiledMap(TMXTiledMap*map)
{
	this->m_map = map;
	//保存meta层的引用
	this->meta = m_map->getLayer("meta");
	this->meta->setVisible(false);
}
Point Player::tileCoordForPosition(Point pos)
{
	Size mapTiledNum = m_map->getMapSize();
	Size tiledSize = m_map->getTileSize();
	//cocos2dx默认坐标y轴由下至上，所以做一个相减操作
	int x = pos.x/tiledSize.width;
	int y = (700 - pos.y) / tiledSize.height;

	if(x > 0)
		x -= 1;
	if( y > 0)
		y -= 0;
	return Point(x,y);
}