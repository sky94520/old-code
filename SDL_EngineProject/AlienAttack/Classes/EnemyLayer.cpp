#include "EnemyLayer.h"
#include "CsvUtil.h"
#include "GameScene.h"
#include "MapLayer.h"
#include "FlyBehavior.h"
#include "ShootBehavior.h"
#include "Bullet.h"
#include "DynamicData.h"

EnemyLayer::EnemyLayer()
	:m_objectIndex(0),m_scrollDistance(0.f)
	,m_pDelegate(nullptr)
{
}
EnemyLayer::~EnemyLayer()
{
}
EnemyLayer*EnemyLayer::create(vector<TMXObject*> objects)
{
	auto layer = new EnemyLayer();
	if(layer && layer->init(objects))
		layer->autoRelease();
	else
		SDL_SAFE_DELETE(layer);
	return layer;
}
bool EnemyLayer::init(vector<TMXObject*> objects)
{
	m_objects = objects;
	//����
	std::sort(m_objects.begin(),m_objects.end(),[](TMXObject*o1,TMXObject*o2)
	{
		return o1->x < o2->x;
	});

	return true;
}
void EnemyLayer::update(float dt)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	m_scrollDistance += m_pDelegate->getMapScrollSpeed();
	//�л��Ƿ�Ӧ�ó���
	for(int i=m_objectIndex;i<m_objects.size();i++)
	{
		auto object = m_objects.at(i);
		//�����л�
		if(m_scrollDistance + visibleSize.width >= object->x)
		{
			Enemy*enemy = this->createEnemy(object);
			enemy->setPositionX(enemy->getPositionX() - m_scrollDistance);
			enemy->setUpdate(true);
			m_objectIndex++;
			//����m_enemys
			m_enemys.push_back(enemy);
		}
		else
			break;
	}
	//�л�ˢ��
	for(auto it = m_enemys.begin();it != m_enemys.end();)
	{
		auto enemy = *it;
		Size s = enemy->getContentSize();
		//�л��Ѿ�����
		if(enemy->isUpdate())
		{
			enemy->update(dt);
		}
		//�л��Ƿ��Ѿ��������߳���
		if(this->isObsolete(enemy))
		{
			//����ǵл������������ӽ��
			if(enemy->isDead())
			{
				DynamicData::getInstance()->alterPlayerGold(enemy->getWorth());
			}
			//�ӵл��������Ƴ�
			it = m_enemys.erase(it);
			//���뵽�����
			this->pushEnemyToPool(enemy);
		}//end if
		else
			it++;
	}
}
vector<Enemy*>& EnemyLayer::getEnemys()
{
	return m_enemys;
}
void EnemyLayer::reset()
{
	//��m_enemys�����ел����뻺�����
	for(auto enemy:m_enemys)
		this->pushEnemyToPool(enemy);
	m_enemys.clear();
	//���þ����
	m_scrollDistance = 0.f;
	m_objectIndex = 0;
}
void EnemyLayer::clear()
{
	this->reset();
	//���������������
	m_objects.clear();
}
bool EnemyLayer::isLevelCompleted()
{
	return m_objectIndex == m_objects.size() && m_enemys.empty();
}
void EnemyLayer::setDelegate(EnemyLayerDelegate*pDelegate)
{
	m_pDelegate = pDelegate;
}
Enemy*EnemyLayer::createEnemy(TMXObject*object)
{
	//auto properties = object->getProperties();
	//��ȡobject����
	auto typeStr = object->type;
	auto type = this->getTypeByString(typeStr);

	auto csv = "csv/enemy.csv";
	//��ȡ����
	int line = CsvUtil::getInstance()->findLineByValue(Value(typeStr),kEnemyProp_Type,csv);
	if(line < 0)
		return nullptr;
	int health = CsvUtil::getInstance()->getValue(line,kEnemyProp_Health,csv).asInt();
	float speed = CsvUtil::getInstance()->getValue(line,kEnemyProp_Speed,csv).asFloat();
	int worth = CsvUtil::getInstance()->getValue(line,kEnemyProp_Worth,csv).asInt();
	float fireInterval = CsvUtil::getInstance()->getValue(line,kEnemyProp_FireInterval,csv).asFloat();
	string normalFormat = CsvUtil::getInstance()->getValue(line,kEnemyProp_NormalFormat,csv).asString();
	int normalCount = CsvUtil::getInstance()->getValue(line,kEnemyProp_NormalCount,csv).asInt();
	string deadFormat = CsvUtil::getInstance()->getValue(line,kEnemyProp_DeadFormat,csv).asString();
	int deadCount = CsvUtil::getInstance()->getValue(line,kEnemyProp_DeadCount,csv).asInt();
	//�󶨾���
	auto spriteName = StringUtils::format(normalFormat.c_str(),0);
	//��������
	Sprite*sprite = Sprite::create(spriteName);
	if(sprite == nullptr)//Ϊ�������ٴδ���
		sprite = Sprite::createWithSpriteFrameName(spriteName);
	Enemy*enemy = this->popEnemyFromPool();//Enemy::create();
	//���ø�������
	enemy->bindSprite(sprite);

	enemy->setType(type);
	enemy->setMaxHp(health);
	enemy->setCurHp(health);
	enemy->setSpeed(speed);
	enemy->setWorth(worth);

	enemy->setShootInterval(fireInterval);
	enemy->setElpased(fireInterval * RANDOM_0_1());
	//������������
	if(normalCount > 1)
	{
		auto normalAnimate = Entity::createAnimate(normalFormat,0,normalCount-1,0.1f,-1);
		enemy->getSprite()->runAction(normalAnimate);
	}
	if(deadCount > 1)
	{
		auto deadAnimate = Entity::createAnimate(deadFormat,0,deadCount-1,0.1f,1);
		enemy->setDeadAction(deadAnimate);
	}
	//������Ϊ
	switch(type)
	{
	case kEnemyType_Glider:
		{
			FlyBehavior*fly = new FlyCrookedly();
			enemy->setFlyBehavior(fly);
		}break;
	case kEnemyType_ShotGlider:
		{
			FlyBehavior*fly = new FlyStraightly();
			enemy->setFlyBehavior(fly);
			//�����ӵ�����
			enemy->setBulletType(kBulletType_Small);
			ShootBehavior*shooter = new SingleShooter(m_pDelegate);
			enemy->setShootBehavior(shooter);
		}break;
	case kEnemyType_Eskeletor:
		{
			enemy->setBulletType(kBulletType_Big);
			//������Ϊ
			enemy->setFlyBehavior(new FlyDown(m_pDelegate));
			enemy->setShootBehavior(new EsketletorShooter(m_pDelegate));
		}break;
	case kEnemyType_Turret:
		{
			enemy->setBulletType(kBulletType_Middle);
			enemy->setFlyBehavior(new FlyWithMap(m_pDelegate));
			enemy->setShootBehavior(new TurretShooter(m_pDelegate));
		}break;
	case kEnemyType_RoofTurret:
		{
			enemy->getSprite()->setFlipY(true);

			enemy->setBulletType(kBulletType_Middle);
			enemy->setFlyBehavior(new FlyWithMap(m_pDelegate));
			enemy->setShootBehavior(new RoofTurretShooter(m_pDelegate));
		}break;
	case kEnemyType_Level1Boss:
		{
			enemy->setBulletType(kBulletType_Big);
			enemy->setFlyBehavior(new Boss1Fly());
		}
	}
	enemy->setPosition(object->x + object->width/2,object->y + object->height/2);
	enemy->setUpdate(false);
	return enemy;
}
EnemyType EnemyLayer::getTypeByString(const string&typeName)
{
	EnemyType type = kEnemyType_None;
	if(typeName == "Glider")
		type = kEnemyType_Glider;
	else if(typeName == "ShotGlider")
		type = kEnemyType_ShotGlider;
	else if(typeName == "Turret")
		type = kEnemyType_Turret;
	else if(typeName == "RoofTurret")
		type = kEnemyType_RoofTurret;
	else if(typeName == "Eskeletor")
		type = kEnemyType_Eskeletor;
	else if(typeName == "Level1Boss")
		type = kEnemyType_Level1Boss;
	return type;
}
bool EnemyLayer::isObsolete(Enemy*enemy)
{
	if(enemy->isDead())
		return true;
	//ֻ�е��л���ʼ����ʱ���ж��Ƿ����
	if(enemy->isUpdate())
	{
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Size s = enemy->getContentSize();
		//Rect r = enemy->getBoundingBox();
		/*if(r.origin.x < 0 || r.origin.x + r.size.width > visibleSize.width
			|| r.origin.y < 0 || r.origin.y +r.size.height > visibleSize.height)*/
		if(enemy->getPositionX() + s.width/2 <= 0)
			return true;
	}
	return false;
}
void EnemyLayer::pushEnemyToPool(Enemy*enemy)
{
	enemy->reset();
	enemy->setVisible(false);
	m_enemyPool.push_back(enemy);
}
Enemy*EnemyLayer::popEnemyFromPool()
{
	Enemy*enemy = nullptr;
	if(m_enemyPool.empty())
	{
		enemy = Enemy::create();
		this->addChild(enemy);
	}
	else
	{
		enemy = m_enemyPool.back();
		m_enemyPool.pop_back();
	}
	enemy->setVisible(true);
	return enemy;
}