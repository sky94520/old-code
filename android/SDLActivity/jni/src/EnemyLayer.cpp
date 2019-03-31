#include "EnemyLayer.h"
#include "Plane.h"
#include "EnemyLayer.h"
#include "FlyBehavior.h"
#include "GameScene.h"
#include "Enemy.h"
#include "DynamicData.h"
#include "SDL.h"

EnemyLayer::EnemyLayer()
	:m_pPlayer(nullptr),m_pDelegate(nullptr)
	,m_pTower(nullptr),m_nChangePos(0)
{
}
EnemyLayer::~EnemyLayer()
{
}
EnemyLayer*EnemyLayer::create( Plane*player,EnemyLayerDelegate*pDelegate)
{
	auto layer = new EnemyLayer();
	if(layer && layer->init(player,pDelegate))
		layer->autoRelease();
	else
		SDL_SAFE_DELETE(layer);
	return layer;
}
bool EnemyLayer::init( Plane*player,EnemyLayerDelegate*pDelegate)
{
	//�����player������
	m_pPlayer = player;
	m_pDelegate = pDelegate;
	
	m_pTower = Sprite::create("boss.png");
	m_pTower->setPosition(400,200);
	this->addChild(m_pTower);

	RotateBy*rotate = RotateBy::create(1.f,360);
	m_pTower->runAction(RepeatForever::create(rotate));

	return true;
}
void EnemyLayer::update(float dt)
{
	//���ɵл�
	if(m_enemies.size() == 0)
	{
		//���������ж��Ƿ����λ��
		this->updateTowerState();

		auto enemy = this->createEnemy();
		this->addChild(enemy);
		m_enemies.push_back(enemy);

		enemy->setDelegate(this);
		//������ɷ���
		this->setEnemyRotation(enemy);
		enemy->setPosition(m_pTower->getPosition());
	}
	for(auto iter = m_enemies.begin();iter != m_enemies.end();)
	{
		auto enemy = *iter;
		//û��������и���
		if(enemy->isDead() == false)
			enemy->update(dt);
		//�������������������
		if(enemy->isAlive() == false)
		{
			auto body = static_cast<b2Body*>(enemy->getUserData());
			PhysicalEngine::getInstance()->destroyBody(body);

			iter = m_enemies.erase(iter);
			enemy->removeFromParent();
			//todo:�Ժ����Ӹ�������Ч
			DynamicData::getInstance()->alterScore(20);
		}
		else
			++iter;
	}
}
void EnemyLayer::reset()
{
	//ɾ�����ڵĵл�
	for(auto iter = m_enemies.begin();iter != m_enemies.end();)
	{
		auto enemy = *iter;
		iter = m_enemies.erase(iter);
		auto body = static_cast<b2Body*>(enemy->getUserData());
		PhysicalEngine::getInstance()->destroyBody(body);
		enemy->removeFromParent();
	}
}
void EnemyLayer::shooting(Plane*plane,BulletType type)
{
	m_pDelegate->shooting(plane,type);
}
Enemy*EnemyLayer::createEnemy()
{
	auto enemy = Enemy::create(m_pPlayer);
	enemy->setCurHp(1);
	enemy->setCurSpeed(1);
	enemy->setAtk(1);
	enemy->setBulletNum(1);

	enemy->setFlyBehavior(new SteadyFly());
	//�����ײ
	b2Body*body = PhysicalEngine::getInstance()->createBox(enemy->getContentSize(),b2_dynamicBody);
	//��Ӵ�����
	/*b2CircleShape sensorShape;
	sensorShape.m_radius = 200/PhysicalEngine::PTM_RATIO/2;
	b2Fixture*sensorFix = body->CreateFixture(&sensorShape,1.f);
	sensorFix->SetSensor(true);
	sensorFix->SetUserData(enemy);

	body->ResetMassData();*/
	//��ӵл���ײ����
	b2Filter filter;
	filter.maskBits = GameScene::ENEMY_MASKBIT;
	filter.categoryBits = GameScene::PLAYER_MASKBIT | GameScene::PLAYER_BULLET_MASKBIT | GameScene::BORDER_MASKBIT;
	auto fixture=body->GetFixtureList();
	fixture->SetFilterData(filter);
	//����ӵ���ײ����
	b2Filter bulletFilter;
	bulletFilter.maskBits = GameScene::ENEMY_BULLET_MASKBIT;
	bulletFilter.categoryBits = GameScene::BORDER_MASKBIT | GameScene::PLAYER_MASKBIT | GameScene::PLAYER_BULLET_MASKBIT;

	enemy->setBulletFilter(bulletFilter);
	body->SetUserData(enemy);
	enemy->setUserData(body);

	return enemy;
}
void EnemyLayer::setEnemyRotation(Enemy*enemy)
{
	float rotation = 0.f;
	int x = m_pTower->getPositionX();
	int y = m_pTower->getPositionY();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//
	if(x > visibleSize.width/2 && y > visibleSize.height/2) rotation = -(rand()%90 + 90);
	else if(x > visibleSize.width/2 && y < visibleSize.height/2) rotation = (rand()%90 + 90);
	else if(x < visibleSize.width/2 && y > visibleSize.height/2) rotation = -rand()%90;
	else if(x < visibleSize.width/2 && y < visibleSize.height/2) rotation = rand()%90;
	
	enemy->getSprite()->setRotation(rotation);
}
void EnemyLayer::updateTowerState()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	m_nChangePos--;
	if(m_nChangePos <= 0)
	{
		m_nChangePos = rand()%5 + 3;
		int x = rand()%((int)visibleSize.width - 200) + 100;
		int y = rand()%((int) visibleSize.height - 100) + 50;
		//���� ����λ�ã�����
		FadeOut*fadeOut = FadeOut::create(0.5f);
		Place*place = Place::create(Point(x,y));
		FadeIn*fadeIn = FadeIn::create(0.5f);

		m_pTower->runAction(Sequence::create(fadeOut,place,fadeIn,nullptr));
	}
}