#include "MapLayer.h"
#include "Player.h"
#include "Entity.h"

MapLayer::MapLayer()
	:m_pTiledMap(nullptr),m_pDelegate(nullptr)
{
}
MapLayer::~MapLayer()
{
}
bool MapLayer::init()
{
	m_pTiledMap = TMXTiledMap::create("level/1.tmx");
	this->addChild(m_pTiledMap);
	//获取砖块对象层
	auto objectGroup = m_pTiledMap->getObjectGroup("tile object layer");
	auto tileObjects = objectGroup->getObjects();
	for(auto object:tileObjects)
		m_tileObjects.push_back(object);
	//获取实体对象层
	auto entityGroup = m_pTiledMap->getObjectGroup("object layer");
	auto &entityObjects = entityGroup->getObjects();
	std::sort(entityObjects.begin(),entityObjects.end(),[](TMXObject*o1,TMXObject*o2)
	{
		return o1->x < o2->x;
	});
	//m_entityObjects.push_back(entityObjects);
	for(auto object : entityObjects)
	{
		m_entityObjects.push_back(object);
	}
	return true;
}
void MapLayer::update(float dt,Player*player)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//判断tiled map是否跟随行动
	Size tileSize = m_pTiledMap->getTileSize();
	Size mapSize = m_pTiledMap->getMapSize();

	Size allSize = Size(mapSize.width*tileSize.width,mapSize.height*tileSize.height);
	//获取当前主角位置
	Point playerPos = player->getPosition();
	if(playerPos.x <= visibleSize.width/2 || playerPos.y >= allSize.width - visibleSize.width/2)
		;
	else
	{
		auto velocity = player->getVelocity();
		auto dis = velocity;
		auto nextPosX = visibleSize.width/2 - playerPos.x;//m_pTiledMap->getPosition() - dis;
		m_pTiledMap->setPositionX(nextPosX);
	}
	//获取当前窗口x轴位置
	auto screenLeft = SDL_fabs(m_pTiledMap->getPositionX());
	auto screenRight = screenLeft + visibleSize.width;
	//是否新建实体对象
	for(auto iter = m_entityObjects.begin(); iter != m_entityObjects.end();)
	{
		auto object = *iter;
		//若在屏幕中，就显示出来
		if(object->x > screenLeft && object->x < screenRight)
		{
			m_pDelegate->createEntityByTMXObject(object);
			//移除这个object
			iter = m_entityObjects.erase(iter);
		}
		else//因为是顺序存储，如果当前没有，那么以后的肯定不会再出现
			break;
	}
}
Point MapLayer::getPlayerBornPos()const
{
	//获取对象层
	auto objectGroup = m_pTiledMap->getObjectGroup("player object layer");
	//获取player
	TMXObject*object = objectGroup->getObject("player");
	
	Point pos = Point(object->x,object->y);
	return pos;
}

int MapLayer::isCollidedTile(const Rect&r,char dir,TMXLayer*layer,const TileCollidedCallback&callback)
{
	//获取碰撞层
	//auto layer = m_pTiledMap->getLayer("collided layer");
	auto mapSize = m_pTiledMap->getMapSize();
	Size tileSize = m_pTiledMap->getTileSize();
	
	int x = int(r.origin.x/tileSize.width);
	int y = int(r.origin.y/tileSize.height);
	int w = int((r.size.width+tileSize.width/2)/tileSize.width);
	int h = int((r.size.height+tileSize.height/2)/tileSize.height);
/*	if(r.size.height > h*tileSize.height)
		h++;
	if(r.size.width < tileSize.width)
		w++;*/
	//进行局部方向判断
	int i=0,j=0;
	if(dir & 0x1)//右
		i = w;
	else if(dir &0x2)//左
		w = 0;
	if(dir & 0x4)//下
	{
		j = h;
//		auto t = r.origin.y - y*tileSize.height;
		//todo
//		if(t > 0.5f)
		{
			h++;
		}
	}
	if(dir & 0x8)//上
		h = 0;
	//保留j的值
	int temp = j;
	for(;i <= w;i++)
	{
		for(j=temp;j <= h;j++)
		{
			Point tileCoordinate = Point(x+i,y+j);

			Sprite*tileSprite = layer->getTileAt(tileCoordinate);

			if(tileSprite)
			{
				Rect rect = tileSprite->getBoundingBox();//Rect((x+i)*tileSize.width,(y+j)*tileSize.height,tileSize.width,tileSize.height);
				if(rect.intersectsRect(r))
				{
					int gid = std::atoi(tileSprite->getName().c_str());
					//只要存在，就回调这个函数
					if(callback)
						gid = callback(layer,tileCoordinate);
					return gid;
				}
			}
		}
	}
	return 0;
}
TMXTiledMap*MapLayer::getTMXTiledMap()const
{
	return m_pTiledMap;
}

void MapLayer::setDelegate(MapLayerDelegate*pDelegate)
{
	m_pDelegate = pDelegate;
}
int MapLayer::entityInteractWithTile(Entity*entity,TMXLayer*layer,const Point&pos)
{
	auto gid = layer->getTileGIDAt(pos);
	auto tileSprite = layer->getTileAt(pos);

	//直接播放碰撞方块音效
	SoundManager::getInstance()->playEffect("sound/mario_collide_tile.ogg",0);
	//判断该方块是否可交互
	ValueMap properties = m_pTiledMap->getTilePropertiesForGID(gid);
	//图块属性集合为空或者没有type属性，则为不可交互图块
	if(properties.empty() || properties.find("type") == properties.end())
	{
		return gid;
	}

	std::string type = properties.at("type").asString();
	
	auto iter = std::find_if(m_tileObjects.begin(),m_tileObjects.end(),[tileSprite](TMXObject*o)
	{
		Point position = Point(o->x+o->width/2,o->y+o->height/2);
		Rect r = tileSprite->getBoundingBox();
		return r.containsPoint(position);
	});
	auto tileHeight = m_pTiledMap->getTileSize().height;
	//运行到这里都会执行动作
	FiniteTimeAction*sequence = nullptr;
	MoveBy*move1 = MoveBy::create(0.05f,Point(0,-tileHeight/4));
	MoveBy*move2 = move1->reverse();
	//图块上升回调函数
	CallFunc*callback = CallFunc::create([this,tileSprite]()
	{
		m_pDelegate->blockUpCallback(tileSprite);
	});
	//(当前砖块是否存在对象，若存在，则通知相应的层)
	if(iter != m_tileObjects.end())
	{
		TMXObject*object = *iter;
		//尝试创建对象
		bool bRet = m_pDelegate->createObjectByTypeAndName(object);
		//只有在创建对象返回true时才会移除该对象
		if(bRet)
				m_tileObjects.erase(iter);
		//重新设置tile id
		CallFunc*end = CallFunc::create([layer,pos,bRet]()
		{
			if(bRet)
			{
				layer->setTileGID(35+1,pos);
			}
		});
		sequence = Sequence::create(move1,callback,move2,end,nullptr);
	}
	//不存在，判断是否能打碎砖块
	else if(entity->isCanBrokeTile())
	{
		//移除这个精灵
		CallFunc*end = CallFunc::create([layer,pos]{
			layer->removeTileAt(pos);
		});
		sequence = Sequence::create(move1,callback,end,nullptr);
		//播放打破砖块的音效
		SoundManager::getInstance()->playEffect("sound/mario_broke_tile.ogg",0);
		m_pDelegate->blockBrokenAction(tileSprite);
	}
	else //不能打碎 只是简单地进行动作
	{
		sequence = Sequence::create(move1,callback,move2,nullptr);
	}
	sequence->setTag(1);
	//当前有动作正在运行时，不再进行动作
	if(tileSprite->getActionByTag(1) != nullptr)
		return gid;
	tileSprite->runAction(sequence);

	return gid;
}
bool MapLayer::optimizePlayerPos(Player*player,Sprite*tileSprite)
{
	//获取碰撞面积
	auto r1 = player->getCollisionBoundingBox();
	auto r2 = tileSprite->getBoundingBox();

	auto inlineFunc = [](float a1,float a2,float b1,float b2)->Point
	{
		float i1 = SDL_min(SDL_max(b1,a1),b2);
		float i2 = SDL_max(SDL_min(b2,a2),b1);
		return Point(i1,i2);
	};
	auto interestVector = inlineFunc(r1.origin.x,r1.origin.x + r1.size.width,
		r2.origin.x,r2.origin.x + r2.size.width);
	/*if(interestVector.x == interestVector.y)
		return false;*/
	auto length = SDL_fabs(interestVector.x - interestVector.y);
	if(length == 0.f)
		length = 1.f;
	//直接设置位置
	if(length <= r1.size.width/2)
	{
		//在左边
		if(r2.origin.x + r2.size.width/2 > interestVector.x)
		{
			player->setPositionX(player->getPositionX() - length);
		}
		else
		{
			player->setPositionX(player->getPositionX() + length);
		}
		return true;
	}
	return false;
}