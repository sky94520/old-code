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
	//��ȡש������
	auto objectGroup = m_pTiledMap->getObjectGroup("tile object layer");
	auto tileObjects = objectGroup->getObjects();
	for(auto object:tileObjects)
		m_tileObjects.push_back(object);
	//��ȡʵ������
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
	//�ж�tiled map�Ƿ�����ж�
	Size tileSize = m_pTiledMap->getTileSize();
	Size mapSize = m_pTiledMap->getMapSize();

	Size allSize = Size(mapSize.width*tileSize.width,mapSize.height*tileSize.height);
	//��ȡ��ǰ����λ��
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
	//��ȡ��ǰ����x��λ��
	auto screenLeft = SDL_fabs(m_pTiledMap->getPositionX());
	auto screenRight = screenLeft + visibleSize.width;
	//�Ƿ��½�ʵ�����
	for(auto iter = m_entityObjects.begin(); iter != m_entityObjects.end();)
	{
		auto object = *iter;
		//������Ļ�У�����ʾ����
		if(object->x > screenLeft && object->x < screenRight)
		{
			m_pDelegate->createEntityByTMXObject(object);
			//�Ƴ����object
			iter = m_entityObjects.erase(iter);
		}
		else//��Ϊ��˳��洢�������ǰû�У���ô�Ժ�Ŀ϶������ٳ���
			break;
	}
}
Point MapLayer::getPlayerBornPos()const
{
	//��ȡ�����
	auto objectGroup = m_pTiledMap->getObjectGroup("player object layer");
	//��ȡplayer
	TMXObject*object = objectGroup->getObject("player");
	
	Point pos = Point(object->x,object->y);
	return pos;
}

int MapLayer::isCollidedTile(const Rect&r,char dir,TMXLayer*layer,const TileCollidedCallback&callback)
{
	//��ȡ��ײ��
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
	//���оֲ������ж�
	int i=0,j=0;
	if(dir & 0x1)//��
		i = w;
	else if(dir &0x2)//��
		w = 0;
	if(dir & 0x4)//��
	{
		j = h;
//		auto t = r.origin.y - y*tileSize.height;
		//todo
//		if(t > 0.5f)
		{
			h++;
		}
	}
	if(dir & 0x8)//��
		h = 0;
	//����j��ֵ
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
					//ֻҪ���ڣ��ͻص��������
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

	//ֱ�Ӳ�����ײ������Ч
	SoundManager::getInstance()->playEffect("sound/mario_collide_tile.ogg",0);
	//�жϸ÷����Ƿ�ɽ���
	ValueMap properties = m_pTiledMap->getTilePropertiesForGID(gid);
	//ͼ�����Լ���Ϊ�ջ���û��type���ԣ���Ϊ���ɽ���ͼ��
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
	//���е����ﶼ��ִ�ж���
	FiniteTimeAction*sequence = nullptr;
	MoveBy*move1 = MoveBy::create(0.05f,Point(0,-tileHeight/4));
	MoveBy*move2 = move1->reverse();
	//ͼ�������ص�����
	CallFunc*callback = CallFunc::create([this,tileSprite]()
	{
		m_pDelegate->blockUpCallback(tileSprite);
	});
	//(��ǰש���Ƿ���ڶ��������ڣ���֪ͨ��Ӧ�Ĳ�)
	if(iter != m_tileObjects.end())
	{
		TMXObject*object = *iter;
		//���Դ�������
		bool bRet = m_pDelegate->createObjectByTypeAndName(object);
		//ֻ���ڴ������󷵻�trueʱ�Ż��Ƴ��ö���
		if(bRet)
				m_tileObjects.erase(iter);
		//��������tile id
		CallFunc*end = CallFunc::create([layer,pos,bRet]()
		{
			if(bRet)
			{
				layer->setTileGID(35+1,pos);
			}
		});
		sequence = Sequence::create(move1,callback,move2,end,nullptr);
	}
	//�����ڣ��ж��Ƿ��ܴ���ש��
	else if(entity->isCanBrokeTile())
	{
		//�Ƴ��������
		CallFunc*end = CallFunc::create([layer,pos]{
			layer->removeTileAt(pos);
		});
		sequence = Sequence::create(move1,callback,end,nullptr);
		//���Ŵ���ש�����Ч
		SoundManager::getInstance()->playEffect("sound/mario_broke_tile.ogg",0);
		m_pDelegate->blockBrokenAction(tileSprite);
	}
	else //���ܴ��� ֻ�Ǽ򵥵ؽ��ж���
	{
		sequence = Sequence::create(move1,callback,move2,nullptr);
	}
	sequence->setTag(1);
	//��ǰ�ж�����������ʱ�����ٽ��ж���
	if(tileSprite->getActionByTag(1) != nullptr)
		return gid;
	tileSprite->runAction(sequence);

	return gid;
}
bool MapLayer::optimizePlayerPos(Player*player,Sprite*tileSprite)
{
	//��ȡ��ײ���
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
	//ֱ������λ��
	if(length <= r1.size.width/2)
	{
		//�����
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