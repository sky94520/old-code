#include "GameScene.h"
#include "Plane.h"
#include "Enemy.h"
#include "PanelLayer.h"
#include "DynamicData.h"

int GameScene::PLAYER_MASKBIT = 0x01;
int GameScene::PLAYER_BULLET_MASKBIT = 0x02;
int GameScene::ENEMY_MASKBIT = 0x04;
int GameScene::ENEMY_BULLET_MASKBIT = 0x08;
int GameScene::BORDER_MASKBIT = 0x10;

GameScene::GameScene()
	:m_pOperateLayer(nullptr),m_pPlayerLayer(nullptr)
	,m_pBulletLayer(nullptr),m_pEnemyLayer(nullptr)
	,m_pPanelLayer(nullptr),m_pGameOverLayer(nullptr)
{
	srand(time(NULL));
}
GameScene::~GameScene()
{
	DynamicData::getInstance()->purge();
}
bool GameScene::init()
{
	//�����߽�
	this->initPhysicalWorld();
	//to_string();
	//ͼ
	Director::getInstance()->getSpriteFrameCache()->addSpriteFramesWithFile("resource.xml");
	Director::getInstance()->getRenderer()->setRenderDrawColor(0,255,255,255);
	//��������
	SoundManager::getInstance()->playBackgroundMusic("music/bg_music.wav",-1);
	//��Ч
	SoundManager::getInstance()->preloadEffect("music/bigplane_bomb.wav");
	SoundManager::getInstance()->preloadEffect("music/bullet.ogg");
	//�����ַ���
	m_pOperateLayer = OperateLayer::create();
	m_pOperateLayer->setDelegate(this);
	this->addChild(m_pOperateLayer);
	//�ӵ���
	m_pBulletLayer = BulletLayer::create();
	this->addChild(m_pBulletLayer);
	//���ǲ�
	m_pPlayerLayer = PlayerLayer::create();
	m_pPlayerLayer->setDelegate(this);
	this->addChild(m_pPlayerLayer);
	//�л���
	m_pEnemyLayer = EnemyLayer::create(m_pPlayerLayer->getPlayer(),this);
	this->addChild(m_pEnemyLayer);
	//����
	m_pPanelLayer = PanelLayer::create();
	this->addChild(m_pPanelLayer);
	//ʧ�ܲ�
	m_pGameOverLayer = GameOverLayer::create();
	m_pGameOverLayer->setDelegate(this);
	m_pGameOverLayer->setVisible(false);
	this->addChild(m_pGameOverLayer,-1);

	this->scheduleUpdate();

	return true;
}
void GameScene::update(float dt)
{
	m_pPlayerLayer->update(dt);
	m_pBulletLayer->update(dt);
	m_pEnemyLayer->update(dt);

	int PTM_RATIO = PhysicalEngine::PTM_RATIO;                
	//��������ģ��
	for(auto body = PhysicalEngine::getInstance()->getBodyList();body;body = body->GetNext())
	{
		//������������ƶ�
		if(body->GetUserData())
		{
			auto entity = static_cast<Entity*>(body->GetUserData());
			//����λ���Լ�����λ��
			auto pos = entity->getPosition();
			auto angle = entity->getSprite()->getRotation();
			//��Ӧ����
			auto b2Pos = b2Vec2(pos.x/PTM_RATIO,pos.y/PTM_RATIO);
			auto degree = SDL_ANGLE_TO_DEGREE(angle);

			body->SetTransform(b2Pos,degree);
		}
	}
	PhysicalEngine::getInstance()->step(dt,0,0);
	//PhysicalEngine::getInstance()->drawDebugData();
}
void GameScene::degreeUpdate(const Point&degree)
{
	m_pPlayerLayer->degreeUpdate(degree);
}
void GameScene::wantShooting()
{
	m_pPlayerLayer->wantShooting();
}
void GameScene::shooting(Plane*plane,BulletType type)
{
	m_pBulletLayer->shooting(plane,type);
	SoundManager::getInstance()->playEffect("music/bullet.ogg",0);
}
void GameScene::gamePause()
{
	//ȡ����ײ
	this->unscheduleUpdate();
	m_pPlayerLayer->onExit();
	m_pBulletLayer->onExit();
	m_pEnemyLayer->onExit();
}
void GameScene::gameResume()
{
	this->scheduleUpdate();
	m_pPlayerLayer->onEnter();
	m_pBulletLayer->onEnter();
	m_pEnemyLayer->onEnter();
}
void GameScene::gameEnd()
{
	this->gamePause();
	m_pGameOverLayer->setVisible(true);
}
void GameScene::gameRestart()
{
	m_pGameOverLayer->setVisible(false);
	this->gameResume();
	//��������������
	DynamicData::getInstance()->reset();
	//�������Ƿɻ�
	m_pPlayerLayer->reset();
	//���õл�
	m_pEnemyLayer->reset();
	m_pBulletLayer->reset();
}
void GameScene::BeginContact(b2Contact*contact)
{
	b2Fixture*fixtureA = contact->GetFixtureA();
	b2Fixture*fixtureB = contact->GetFixtureB();
	b2Body*bodyA = fixtureA->GetBody();
	b2Body*bodyB = fixtureB->GetBody();
	b2Filter filterA = fixtureA->GetFilterData();
	b2Filter filterB = fixtureB->GetFilterData();
	//����Ǵ��������ض���enemy
	/*if(fixtureA->IsSensor())
	{
		auto enemy = static_cast<Enemy*>(fixtureB->GetUserData());
		enemy->flee();
		return;
	}
	else if(fixtureB->IsSensor())
	{
		auto enemy = static_cast<Enemy*>(fixtureB->GetUserData());
		enemy->flee();
		return;
	}*/
	//�ᷢ������ײ
	if(filterA.maskBits == BORDER_MASKBIT)
	{
		Entity*entity = static_cast<Entity*>(bodyB->GetUserData());
		entity->hurt(100);
	}
	else if(filterB.maskBits == BORDER_MASKBIT)
	{
		Entity*entity = static_cast<Entity*>(bodyA->GetUserData());
		entity->hurt(100);
	}
	else
	{
		Entity*entityA = static_cast<Entity*>(bodyA->GetUserData());
		Entity*entityB = static_cast<Entity*>(bodyB->GetUserData());
		//�����˺�
		entityA->hurt(entityB->getAtk());
		entityB->hurt(entityA->getAtk());
	}
}
void GameScene::EndContact(b2Contact*contact)
{
}
void GameScene::initPhysicalWorld()
{
	Size s = Director::getInstance()->getVisibleSize();
	auto physicalEngine = PhysicalEngine::getInstance();
	//��ʼ����������
	physicalEngine->initPhysicalWorld();
	b2Body*bodyes[4];
	//�����߽� top
	bodyes[0] = physicalEngine->createEdge(Point(0,0),Point(s.width,0),b2BodyType::b2_staticBody);
	//bottom
	bodyes[1] = physicalEngine->createEdge(Point(0,s.height),Point(s.width,s.height),b2BodyType::b2_staticBody);
	//left
	bodyes[2] = physicalEngine->createEdge(Point(0,0),Point(0,s.height),b2BodyType::b2_staticBody);
	//right
	bodyes[3] = physicalEngine->createEdge(Point(s.width,0),Point(s.width,s.height),b2BodyType::b2_staticBody);
	//�����ײ����
	b2Filter filter;
	filter.maskBits = GameScene::BORDER_MASKBIT;
	filter.categoryBits = PLAYER_MASKBIT|PLAYER_BULLET_MASKBIT|ENEMY_MASKBIT|ENEMY_BULLET_MASKBIT;
	for(auto body:bodyes)
	{
		b2Fixture*fixture = body->GetFixtureList();
		fixture->SetFilterData(filter);
	}
	//�����ײ�¼�����
	physicalEngine->setContactListener(this);
}
