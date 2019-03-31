#include "GameScene.h"
#include "MapLayer.h"
#include "Player.h"
#include "DynamicData.h"
#include "BulletLayer.h"
#include "PanelLayer.h"
#include "CsvUtil.h"

GameScene::GameScene()
	:m_pMapLayer(nullptr),m_pPlayerLayer(nullptr)
	,m_pEventLayer(nullptr),m_pBulletLayer(nullptr)
	,m_pEnemyLayer(nullptr),m_pPanelLayer(nullptr)
	,m_pGameOverLayer(nullptr)
{
}
GameScene::~GameScene()
{
	DynamicData::getInstance()->purge();
	CsvUtil::getInstance()->purge();
}
GameScene*GameScene::create(const string&level)
{
	auto scene = new GameScene();
	if(scene && scene->init(level))
		scene->autoRelease();
	else
		SDL_SAFE_DELETE(scene);
	return scene;
}
bool GameScene::init(const string&level)
{
	Director::getInstance()->getRenderer()->setRenderDrawColor(0,255,255,255);
	//����ͼƬ��Դ
	Director::getInstance()->getSpriteFrameCache()->addSpriteFramesWithFile("sprite/heli.xml");
	Director::getInstance()->getSpriteFrameCache()->addSpriteFramesWithFile("sprite/largeexplosion.xml");
	Director::getInstance()->getSpriteFrameCache()->addSpriteFramesWithFile("sprite/smallexplosion.xml");
	Director::getInstance()->getSpriteFrameCache()->addSpriteFramesWithFile("sprite/explosion.xml");
	Director::getInstance()->getSpriteFrameCache()->addSpriteFramesWithFile("sprite/enemy3.xml");
	Director::getInstance()->getSpriteFrameCache()->addSpriteFramesWithFile("sprite/gameover.xml");
	Director::getInstance()->getSpriteFrameCache()->addSpriteFramesWithFile("sprite/coin.xml");
	Director::getInstance()->getSpriteFrameCache()->addSpriteFramesWithFile("sprite/shop.xml");
	//����csv
	CsvUtil::getInstance()->loadFile("csv/bullet.csv");
	CsvUtil::getInstance()->loadFile("csv/enemy.csv");
	//��ȡ�ļ��������Ӧ�����������޵�ʱ��
	CsvUtil::getInstance()->loadFile(LIFE_CSV_PATH);
	CsvUtil::getInstance()->loadFile(RESSURECT_CSV_PATH);
	DynamicData::getInstance();
	//�¼���
	m_pEventLayer = KeyboardLayer::create();
	m_pEventLayer->setDelegate(this);
	this->addChild(m_pEventLayer);
	//��ͼ��
	m_pMapLayer = MapLayer::create(level);
	this->addChild(m_pMapLayer);
	//���ǲ�
	m_pPlayerLayer = PlayerLayer::create();
	m_pPlayerLayer->setDelegate(this);
	this->addChild(m_pPlayerLayer);
	//�ӵ���
	m_pBulletLayer = BulletLayer::create();
	this->addChild(m_pBulletLayer);
	//�л���
	m_pEnemyLayer = EnemyLayer::create(m_pMapLayer->getTMXObjects());
	m_pEnemyLayer->setDelegate(this);
	this->addChild(m_pEnemyLayer);
	//����
	m_pPanelLayer = PanelLayer::create();
	this->addChild(m_pPanelLayer);
	//��Ϸ������
	m_pGameOverLayer = GameOverLayer::create();
	m_pGameOverLayer->setVisible(false);
	m_pGameOverLayer->setDelegate(this);
	this->addChild(m_pGameOverLayer);

	this->scheduleUpdate();
	return true;
}
void GameScene::update(float dt)
{
	m_pMapLayer->update(dt);
	m_pPlayerLayer->update(dt);
	m_pBulletLayer->update(dt);
	m_pEnemyLayer->update(dt);

	this->handleCollision();
	//�ؿ��Ƿ����
	if(m_pEnemyLayer->isLevelCompleted())
	{
		this->nextLevel();
	}
}
void GameScene::operateAllSchedulerAndActions(Node*node,GameState state)
{
	switch(state)
	{
	case kGameState_Pause:node->pauseSchedulerAndActions();
		break;
	case kGameState_Resume:node->resumeSchedlerAndActions();
		break;
	}
	const std::vector<Node*>& children = node->getChildren();
	for(auto child:children)
	{
		this->operateAllSchedulerAndActions(child,state);
	}
}
void GameScene::gamePause()
{
	this->operateAllSchedulerAndActions(m_pMapLayer,kGameState_Pause);
	this->operateAllSchedulerAndActions(m_pPlayerLayer,kGameState_Pause);
	this->operateAllSchedulerAndActions(m_pBulletLayer,kGameState_Pause);
	this->operateAllSchedulerAndActions(m_pEnemyLayer,kGameState_Pause);

	this->unscheduleUpdate();
}
void GameScene::gameResume()
{
	this->operateAllSchedulerAndActions(m_pMapLayer,kGameState_Resume);
	this->operateAllSchedulerAndActions(m_pPlayerLayer,kGameState_Resume);
	this->operateAllSchedulerAndActions(m_pBulletLayer,kGameState_Resume);
	this->operateAllSchedulerAndActions(m_pEnemyLayer,kGameState_Resume);

	this->scheduleUpdate();
}
MapLayer*GameScene::getMapLayer()
{
	return m_pMapLayer;
}
BulletLayer*GameScene::getBulletLayer()
{
	return m_pBulletLayer;
}
void GameScene::handleCollision()
{
	Player*player = m_pPlayerLayer->getPlayer();
	auto playerBullets = m_pBulletLayer->getPlayerBullets();
	auto enemyBullets = m_pBulletLayer->getEnemyBullets();

	auto enemys = m_pEnemyLayer->getEnemys();
	//�����ӵ��͵л�
	for(auto bullet:playerBullets)
	{
		if(bullet->isDying())
			continue;
		for(auto enemy:enemys)
		{
			//���л���������δ���£��������ײ
			if(enemy->isDying() || enemy->isUpdate() == false)
				continue;
			auto r1 = bullet->getBoundingBox();
			auto r2 = enemy->getBoundingBox();
			if(r1.intersectsRect(r2))
			{
				bullet->hurt(100);
				enemy->hurt(bullet->getDamage());
			}
		}
	}
	//�����޵У���������ײ
	if(player->isInvulnerable() == false)
	{
		//���Ǻ͵�ͼ��ײ�����ײ,����MapLayer
		m_pMapLayer->checkCollisionBetweenPlayerAndMap(player);
		//���Ǻ͵л���ײ
		auto r = player->getBoundingBox();
		for(auto enemy:enemys)
		{
			auto r1 = enemy->getBoundingBox();
			if(r.intersectsRect(r1))
			{
				player->hurt(100);
				//enemy->hurt(1);
			}
		}
		//���Ǻ͵л��ӵ�
		for(auto bullet:enemyBullets)
		{
			if(bullet->isDying())
				continue;
			auto r2 = bullet->getBoundingBox();
			if(r.intersectsRect(r2))
			{
				player->hurt(bullet->getDamage());
				bullet->hurt(1);
			}
		}
	}
}
void GameScene::nextLevel()
{
	string level = "level/map2.tmx";
	//�����ӵ���
	m_pBulletLayer->reset();
	//���¼��ص�ͼ
	m_pMapLayer->clear();
	m_pMapLayer->init(level);
	//�������ɵл�
	m_pEnemyLayer->clear();
	m_pEnemyLayer->init(m_pMapLayer->getTMXObjects());
	//������������
	m_pPlayerLayer->resetPlayer();
}
void GameScene::playerMove(const Point&velocity)
{
	m_pPlayerLayer->playerMove(velocity);
}
void GameScene::playerWantShooting()
{
	Player*player = m_pPlayerLayer->getPlayer();
	if(player->isDying())
		return;
	Rect r = player->getBoundingBox();
	Point startPos = Point(r.origin.x+r.size.width,r.origin.y+r.size.height/2);

	m_pBulletLayer->addPlayerBullet(startPos,kBulletType_Small,Point(1.f,0.f));
}
void GameScene::gameOver()
{
	//��ͣ��������
	this->gamePause();

	m_pGameOverLayer->setVisible(true);
}
void GameScene::gameRestart()
{
	//������Ϸ
	DynamicData::getInstance()->reset();
	m_pEnemyLayer->reset();
	m_pBulletLayer->reset();
	m_pMapLayer->reset();

	m_pGameOverLayer->setVisible(false);
	//�ָ���Ϸ
	this->gameResume();
}
float GameScene::getMapScrollSpeed()
{
	return m_pMapLayer->getScrollSpeed();
}
bool GameScene::addEnemyBullet(const Point&startPos,BulletType type,const Point&heading)
{
	return m_pBulletLayer->addEnemyBullet(startPos,type,heading);
}