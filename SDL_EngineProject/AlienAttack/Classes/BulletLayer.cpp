#include "BulletLayer.h"
#include "CsvUtil.h"
#include "GameScene.h"
#include "MapLayer.h"

BulletLayer::BulletLayer()
{
	vector<Bullet*> bullets;
	m_bullets.insert(make_pair("player",bullets));
	m_bullets.insert(make_pair("enemy",bullets));
}
BulletLayer::~BulletLayer()
{
}
bool BulletLayer::init()
{
	return true;
}
void BulletLayer::update(float dt)
{
	//�����ӵ��ĸ�������� ��ײ����GameScene
	for(auto iterMap = m_bullets.begin();iterMap!=m_bullets.end();++iterMap)
	{
		vector<Bullet*>&bullets = iterMap->second;
		for(auto iter = bullets.begin();iter != bullets.end();)
		{
			auto bullet = *iter;
			//�������߳���,�Ƴ�
			if(this->isObsolete(bullet))
			{
				iter = bullets.erase(iter);
				//�����ӵ�����
				this->pushBulletToPool(bullet);
			}
			else//�����������
			{
				//δ�����������Լ����ٶ�
				if(bullet->isDying() == false)
				{
					auto nextPos = bullet->getPosition() + bullet->getHeading()*bullet->getSpeed();
					bullet->setPosition(nextPos);
				}
				else//������������ͼ�ƶ�
				{
					//todo
					auto scene = (GameScene*)this->getParent();
					float scrollSpeed = scene->getMapLayer()->getScrollSpeed();

					auto nextPos = bullet->getPosition() + Point(-scrollSpeed,0.f);
					bullet->setPosition(nextPos);
				}
				++iter;
			}
		}//end for
	}//end for
}
bool BulletLayer::addPlayerBullet(const Point&startPos,BulletType type,const Point&heading)
{
	Bullet*bullet = this->createBullet(type);
	if(bullet)
	{
		bullet->setPosition(startPos);
		bullet->setHeading(Point(heading.x,heading.y));
		
		auto& bullets = m_bullets.at("player");
		bullets.push_back(bullet);

		return true;
	}
	return false;
}
bool BulletLayer::addEnemyBullet(const Point&startPos,BulletType type,const Point&heading)
{
	Bullet*bullet = this->createBullet(type);
	if(bullet)
	{
		bullet->setPosition(startPos);
		
		bullet->setHeading(Point(heading.x,heading.y));

		auto& bullets = m_bullets.at("enemy");
		bullets.push_back(bullet);

		return true;
	}
	return false;
}
std::vector<Bullet*>& BulletLayer::getEnemyBullets()
{
	return m_bullets.at("enemy");
}
std::vector<Bullet*>& BulletLayer::getPlayerBullets()
{
	return m_bullets.at("player");
}
void BulletLayer::reset()
{
	//�����ӵ�
	for(auto iterMap = m_bullets.begin();iterMap!=m_bullets.end();++iterMap)
	{
		vector<Bullet*>&bullets = iterMap->second;
		for(auto iter = bullets.begin();iter != bullets.end();)
		{
			auto bullet = *iter;
			this->pushBulletToPool(bullet);
			iter = bullets.erase(iter);
		}
	}
}
Bullet*BulletLayer::createBullet(BulletType type)
{
	//��ȡ��Ӧ�ӵ�������
	auto csvUtil = CsvUtil::getInstance();
	//��ȡ��������Ӧ���ַ���
	auto typeStr = this->getStringByType(type);
	int line = csvUtil->findLineByValue(Value(typeStr),kBulletProp_Type,"csv/bullet.csv");
	if(line < 0)
		return nullptr;
	float speed = csvUtil->getValue(line,kBulletProp_Speed,"csv/bullet.csv").asFloat();
	float damage = csvUtil->getValue(line,kBulletProp_Damage,"csv/bullet.csv").asFloat();
	auto normalFormat = csvUtil->getValue(line,kBulletProp_NormalFormat,"csv/bullet.csv").asString();
	auto normalCount = csvUtil->getValue(line,kBulletProp_NormalCount,"csv/bullet.csv").asInt();
	auto deadFormat = csvUtil->getValue(line,kBulletProp_DeadFormat,"csv/bullet.csv").asString();
	auto deadCount = csvUtil->getValue(line,kBulletProp_DeadCount,"csv/bullet.csv").asInt();

	auto spriteName = StringUtils::format(normalFormat.c_str(),0);
	Sprite*sprite = Sprite::create(spriteName);
	//����������Ϊ��0��ʼ���ʼ�һ
	auto deadAnimate = Entity::createAnimate(deadFormat,0,deadCount - 1,0.1f,1);

	Bullet*bullet = this->popBulletFromPool();
	bullet->setPosition(0.f,0.f);
	bullet->bindSprite(sprite);
	//������������
	bullet->setDeadAction(deadAnimate);
	bullet->setBulletType(type);
	bullet->setSpeed(speed);
	bullet->setDamage(damage);

	bullet->setMaxHp(1);
	bullet->setCurHp(1);

	return bullet;
}
bool BulletLayer::isObsolete(Bullet*bullet)const
{
	if(bullet->isDead())
		return true;
	else
	{
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Rect r = bullet->getBoundingBox();
		if(r.origin.x < 0 || r.origin.x + r.size.width > visibleSize.width
			|| r.origin.y < 0 || r.origin.y +r.size.height > visibleSize.height)
			return true;
	}
	return false;
}
std::string BulletLayer::getStringByType(BulletType type)
{
	std::string str;
	switch(type)
	{
	case kBulletType_Small:str = "bullet1";break;
	case kBulletType_Middle:str = "bullet2";break;
	case kBulletType_Big:str = "bullet3";break;
	}
	return str;
}
Bullet*BulletLayer::popBulletFromPool()
{
	Bullet*bullet = nullptr;
	if(m_bulletPool.empty())
	{
		bullet = Bullet::create();
		this->addChild(bullet);
	}
	else
	{
		bullet = m_bulletPool.back();
		m_bulletPool.pop_back();
	}
	bullet->setVisible(true);
	return bullet;
}
void BulletLayer::pushBulletToPool(Bullet*bullet)
{
	m_bulletPool.push_back(bullet);
	bullet->setVisible(false);
	bullet->reset();
}