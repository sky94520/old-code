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
	//加载图片资源
	Director::getInstance()->getSpriteFrameCache()->addSpriteFramesWithFile("sprite/heli.xml");
	Director::getInstance()->getSpriteFrameCache()->addSpriteFramesWithFile("sprite/largeexplosion.xml");
	Director::getInstance()->getSpriteFrameCache()->addSpriteFramesWithFile("sprite/smallexplosion.xml");
	Director::getInstance()->getSpriteFrameCache()->addSpriteFramesWithFile("sprite/explosion.xml");
	Director::getInstance()->getSpriteFrameCache()->addSpriteFramesWithFile("sprite/enemy3.xml");
	Director::getInstance()->getSpriteFrameCache()->addSpriteFramesWithFile("sprite/gameover.xml");
	Director::getInstance()->getSpriteFrameCache()->addSpriteFramesWithFile("sprite/coin.xml");
	Director::getInstance()->getSpriteFrameCache()->addSpriteFramesWithFile("sprite/shop.xml");
	//加载csv
	CsvUtil::getInstance()->loadFile("csv/bullet.csv");
	CsvUtil::getInstance()->loadFile("csv/enemy.csv");
	//读取文件来获得响应的生命数和无敌时间
	CsvUtil::getInstance()->loadFile(LIFE_CSV_PATH);
	CsvUtil::getInstance()->loadFile(RESSURECT_CSV_PATH);
	DynamicData::getInstance();
	//事件层
	m_pEventLayer = KeyboardLayer::create();
	m_pEventLayer->setDelegate(this);
	this->addChild(m_pEventLayer);
	//地图层
	m_pMapLayer = MapLayer::create(level);
	this->addChild(m_pMapLayer);
	//主角层
	m_pPlayerLayer = PlayerLayer::create();
	m_pPlayerLayer->setDelegate(this);
	this->addChild(m_pPlayerLayer);
	//子弹层
	m_pBulletLayer = BulletLayer::create();
	this->addChild(m_pBulletLayer);
	//敌机层
	m_pEnemyLayer = EnemyLayer::create(m_pMapLayer->getTMXObjects());
	m_pEnemyLayer->setDelegate(this);
	this->addChild(m_pEnemyLayer);
	//面板层
	m_pPanelLayer = PanelLayer::create();
	this->addChild(m_pPanelLayer);
	//游戏结束层
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
	//关卡是否完成
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
	//主角子弹和敌机
	for(auto bullet:playerBullets)
	{
		if(bullet->isDying())
			continue;
		for(auto enemy:enemys)
		{
			//当敌机死亡或者未更新，不检测碰撞
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
	//主角无敌，不参与碰撞
	if(player->isInvulnerable() == false)
	{
		//主角和地图碰撞层的碰撞,交给MapLayer
		m_pMapLayer->checkCollisionBetweenPlayerAndMap(player);
		//主角和敌机碰撞
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
		//主角和敌机子弹
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
	//重置子弹层
	m_pBulletLayer->reset();
	//重新加载地图
	m_pMapLayer->clear();
	m_pMapLayer->init(level);
	//重新生成敌机
	m_pEnemyLayer->clear();
	m_pEnemyLayer->init(m_pMapLayer->getTMXObjects());
	//重新设置主角
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
	//暂停其他界面
	this->gamePause();

	m_pGameOverLayer->setVisible(true);
}
void GameScene::gameRestart()
{
	//重置游戏
	DynamicData::getInstance()->reset();
	m_pEnemyLayer->reset();
	m_pBulletLayer->reset();
	m_pMapLayer->reset();

	m_pGameOverLayer->setVisible(false);
	//恢复游戏
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