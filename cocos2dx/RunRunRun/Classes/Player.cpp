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
	//��������֡������ӵ��б���
	for(int i = 1;i <= 15;i++)
	{
		frame = frameCache->getSpriteFrameByName(StringUtils::format("run%d.png",i));
		frameList.pushBack(frame);
	}
	//���ݾ���֡���󴴽���������
	Animation*animation = Animation::createWithSpriteFrames(frameList);
	//һֱѭ��
	animation->setLoops(-1);
	//ÿ֡����ʱ����
	animation->setDelayPerUnit(0.08f);
	//������������
	Animate*animate = Animate::create(animation);
	//����ִ�ж���
	 m_sprite->runAction(animate);
	
}
void Player::setViewPointByPlayer()
{
	if(m_sprite == NULL)
		return ;
	Layer*parent = (Layer*)getParent();
	//��ͼ��������
	Size mapTiledNum = m_map->getMapSize();
	//��ͼ�������Ӵ�С
	Size tiledSize = m_map->getTileSize();
	//map��С
	Size mapSize = Size(
	mapTiledNum.width * tiledSize.width,
		mapTiledNum.height * tiledSize.height);
	//��Ļ��С
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//��������
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
	//ȡ����ǰ��������
	Size spriteSize = m_sprite->getContentSize();
	Point dstPos = Point(x + spriteSize.width/2,y);
	//��ȡ��ǰ����ǰ�������ڵ�ͼ�е¸���λ��
	Point tiledPos = tileCoordForPosition(Point(dstPos.x,dstPos.y));
	//��ȡ��ͼ���ӵ�Ψһ��ʶID
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
	//����meta�������
	this->meta = m_map->getLayer("meta");
	this->meta->setVisible(false);
}
Point Player::tileCoordForPosition(Point pos)
{
	Size mapTiledNum = m_map->getMapSize();
	Size tiledSize = m_map->getTileSize();
	//cocos2dxĬ������y���������ϣ�������һ���������
	int x = pos.x/tiledSize.width;
	int y = (700 - pos.y) / tiledSize.height;

	if(x > 0)
		x -= 1;
	if( y > 0)
		y -= 0;
	return Point(x,y);
}