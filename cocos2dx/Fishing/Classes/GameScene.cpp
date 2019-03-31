#include "GameScene.h"
#include "FishLayer.h"
#include "Fork.h"
#include "Fish.h"
#include "LuaEngine.h"
#include "PhysicalEngine.h"
#include "DynamicData.h"
#include "PanelLayer.h"
#include "LevelLayer.h"
#include "KnowledgeLayer.h"
#include "QuestionLayer.h"
#include "Toast.h"

GameScene::GameScene()
	:m_pGameLayer(nullptr),m_pFishLayer(nullptr)
	,m_pTouchLayer(nullptr),m_pHelpLayer(nullptr)
	,m_pPanelLayer(nullptr),m_pPauseLayer(nullptr)
	,m_pDefeatLayer(nullptr),m_pSuccessLayer(nullptr)
	,m_nCurLevel(0)
{
}
GameScene::~GameScene()
{
	/*没必要清除这个，而且在转到LevelLayer时，
	因为先LevelLayer::create()再purge,再次GameScene::create()
	就相当于main.lua并没有加载，从而报错*/
	//LuaEngine::getInstance()->purge();
	DynamicData::getInstance()->purge();
	PhysicalEngine::getInstance()->purge();
}
GameScene*GameScene::create(int level)
{
	auto scene = new GameScene();
	if(scene && scene->init(level))
		scene->autorelease();
	else
		CC_SAFE_DELETE(scene);
	return scene;
}
bool GameScene::init(int level)
{
	//加载资源
	auto spriteFrameCache = SpriteFrameCache::getInstance();
	spriteFrameCache->addSpriteFramesWithFile("fish.plist");
	//加载脚本
	//LuaEngine::getInstance()->dofile("main.lua");
	//设置当前关卡
	m_nCurLevel = level;
	std::string levelStr = StringUtils::format("level/level%d.lua",m_nCurLevel);
	this->loadLevel(levelStr);
	//事件分发层
	m_pTouchLayer = TouchLayer::create();
	m_pTouchLayer->setDelegate(this);
	this->addChild(m_pTouchLayer);
	//背景层
	Size visibleSize = Director::getInstance()->getVisibleSize();

	Sprite*bg = Sprite::create("background.jpg");
	bg->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(bg,-1);
	//捕鱼帮助层
	m_pHelpLayer = HelpLayer::create();
	m_pHelpLayer->setDelegate(this); 
	this->addChild(m_pHelpLayer);
	//面板层
	m_pPanelLayer = PanelLayer::create();
	m_pPanelLayer->setDelegate(this);
	this->addChild(m_pPanelLayer);
	//游戏层
	m_pGameLayer = GameLayer::create();
	this->addChild(m_pGameLayer);
	//fish layer
	m_pFishLayer = FishLayer::create();
	this->addChild(m_pFishLayer);
	//暂停层 默认不显示
	m_pPauseLayer = PauseLayer::create();
	m_pPauseLayer->setVisible(false);
	m_pPauseLayer->setDelegate(this);

	m_pPanelLayer->initWithTimes();
	m_pPanelLayer->initWithNeedfulFishes();
	this->addChild(m_pPauseLayer);
	//失败层
	m_pDefeatLayer = DefeatLayer::create();
	m_pDefeatLayer->setVisible(false);
	m_pDefeatLayer->setDelegate(this);
	this->addChild(m_pDefeatLayer);
	//成功层
	m_pSuccessLayer = SuccessLayer::create();
	m_pSuccessLayer->setVisible(false);
	m_pSuccessLayer->setDelegate(this);
	this->addChild(m_pSuccessLayer);
	
	//开启update
	this->scheduleUpdate();
	//添加碰撞监听器
	PhysicalEngine::getInstance()->SetContactListener(this);

	return true;
}
void GameScene::update(float dt)
{
	PhysicalEngine::getInstance()->update(dt);

	m_pFishLayer->update(dt);
	m_pHelpLayer->update(dt);
}
void GameScene::loadLevel(const std::string&filename)
{
	//加载脚本
	LuaEngine::getInstance()->dofile(filename);
	//获取限制条件
	DynamicData::getInstance()->initlize();
	//设置折射偏移 向左x，向上y
	DynamicData::getInstance()->setOffsetRefraction(Point(-25,30));
}
void GameScene::shoot(const Point&targetPos)
{
	//如果此时显示了组件，则隐藏
	if(m_pPanelLayer->isShowAllComp())
	{
		m_pPanelLayer->hideAllNeedfulFishesComp();
		m_pPanelLayer->setShowAllComp(false);
	}

	auto fork = m_pGameLayer->getFork();
	if(fork->isShooting())
		return;
	//在小图上显示鱼叉运行轨迹
	m_pHelpLayer->showHelpfulFork(targetPos);

	fork->setVisible(true);
	fork->shoot(targetPos);
	//减少出手次数 同时判断步数是否剩余
	auto defead = DynamicData::getInstance()->reduceAtkTimes();
	//任务失败
	if(defead == false)
	{
		//游戏暂停
		this->operateAllSchedulerAndActions(m_pTouchLayer,GameState::kOperatePause);
		this->operateAllSchedulerAndActions(m_pFishLayer,GameState::kOperatePause);
		this->operateAllSchedulerAndActions(m_pHelpLayer,GameState::kOperatePause);
		this->unscheduleUpdate();
		//显示失败界面
		m_pDefeatLayer->setVisible(true);
		return;
	}
}
void GameScene::BeginContact(b2Contact* contact)
{
	b2Fixture*fixtureA = contact->GetFixtureA();
	b2Fixture*fixtureB = contact->GetFixtureB();
	b2Filter filterA = fixtureA->GetFilterData();
	b2Filter filterB = fixtureB->GetFilterData();
	Entity*entity1 = static_cast<Entity*>(contact->GetFixtureA()->GetBody()->GetUserData());
	Entity*entity2 = static_cast<Entity*>(contact->GetFixtureB()->GetBody()->GetUserData());
	if(entity1->isVisible() == false || entity2->isVisible() == false)
		return;
	bool success = false;
	//a 惊吓面积 b鱼叉
	if((filterA.categoryBits == 0x02 && filterB.categoryBits == 0x04))
	{
		Fish*fish = static_cast<Fish*>(entity1);
		fish->runScaredAnimation();
	}
	//a 鱼叉 b惊吓面积
	else if(filterA.categoryBits == 0x04 && filterB.categoryBits == 0x02)
	{
			Fish*fish = static_cast<Fish*>(entity2);
			fish->runScaredAnimation();
	}
	//a 鱼 b 鱼叉
	else if(filterA.categoryBits == 0x01 && filterB.categoryBits == 0x04)
	{
		Fork*fork = static_cast<Fork*>(entity2);
		//只有在鱼叉正在捕鱼时才会进行碰撞判定
		if(fork->isShooting() == true)
		{
			Fish*fish = static_cast<Fish*>(entity1);
			fish->catched();
			//抓到鱼后判断是否满足过关条件
			success = DynamicData::getInstance()->reduceFish(fish->getID());
		}
	}
	//a鱼叉 b鱼
	else if(filterA.categoryBits == 0x04 && filterB.categoryBits == 0x01)
	{
		Fork*fork = static_cast<Fork*>(entity1);
		//只有在鱼叉正在捕鱼时才会进行碰撞判定
		if(fork->isShooting() == true)
		{
			Fish*fish = static_cast<Fish*>(entity2);
			fish->catched();
			success = DynamicData::getInstance()->reduceFish(fish->getID());
		}
	}
	//成功过关
	if(success)
	{
		//暂停
		this->operateAllSchedulerAndActions(m_pTouchLayer,GameState::kOperatePause);
		this->operateAllSchedulerAndActions(m_pFishLayer,GameState::kOperatePause);
		this->operateAllSchedulerAndActions(m_pHelpLayer,GameState::kOperatePause);
		this->unscheduleUpdate();

		m_pSuccessLayer->setVisible(true);
	}
}
void GameScene::EndContact(b2Contact* contact)
{
}
void GameScene::draw(Renderer* renderer, const Mat4 &transform, uint32_t flags)
{
	_command.init(_globalZOrder);
	_command.func = CC_CALLBACK_0(GameScene::onDraw,this,transform,flags);
	renderer->addCommand(&_command);
}
void GameScene::onDraw(const Mat4 &transform, uint32_t flags)
{
	kmGLPushMatrix();
	kmGLLoadMatrix(&transform);
	//PhysicalEngine::getInstance()->debugDraw();
	//绘制鱼 辅助层
	m_pHelpLayer->debugDraw();
	kmGLPopMatrix();
}
Vector<Fish*>* GameScene::getShowingFishes()
{
	return m_pFishLayer->getFishes();
}
Fork*GameScene::getShowingFork()
{
	return m_pGameLayer->getFork();
}
bool GameScene::isClickComponents(const Point&pos)
{
	//是否点击了组件
	if(m_pPanelLayer->isClickedComponents(pos) == true)
	{
		//如果已经显示了所有 鱼的组件 hide
		if(m_pPanelLayer->isShowAllComp())
		{
			m_pPanelLayer->hideAllNeedfulFishesComp();
			m_pPanelLayer->setShowAllComp(false);
		}
		else
		{
			m_pPanelLayer->showAllNeedfulFishesComp();
			m_pPanelLayer->setShowAllComp(true);
		}
		return true;
	}
	return false;
}
void GameScene::gamePause()
{
	this->operateAllSchedulerAndActions(m_pTouchLayer,GameState::kOperatePause);
	this->operateAllSchedulerAndActions(m_pFishLayer,GameState::kOperatePause);
	this->operateAllSchedulerAndActions(m_pHelpLayer,GameState::kOperatePause);
	this->unscheduleUpdate();
	//显示暂停界面
	m_pPauseLayer->setVisible(true);
}
void GameScene::gameResume()
{
	this->operateAllSchedulerAndActions(m_pTouchLayer,GameState::kOperateResume);
	this->operateAllSchedulerAndActions(m_pFishLayer,GameState::kOperateResume);
	this->operateAllSchedulerAndActions(m_pHelpLayer,GameState::kOperateResume);

	this->scheduleUpdate();
	//关闭暂停界面
	m_pPauseLayer->setVisible(false);
}
void GameScene::gameRestart()
{
	//恢复
	this->operateAllSchedulerAndActions(m_pTouchLayer,GameState::kOperateResume);
	this->operateAllSchedulerAndActions(m_pFishLayer,GameState::kOperateResume);
	this->operateAllSchedulerAndActions(m_pHelpLayer,GameState::kOperateResume);
	
	//重置过关条件等
	DynamicData::getInstance()->clean();
	m_pPanelLayer->clean();

	DynamicData::getInstance()->initlize();

	m_pPanelLayer->initWithTimes();
	m_pPanelLayer->initWithNeedfulFishes();

	m_pFishLayer->reset();

	this->scheduleUpdate();
}
void GameScene::nextLevel()
{
	//判断是否到下一关卡了
	int level = m_nCurLevel + 1;
	int levelCount = DynamicData::getInstance()->getLevelCount();
	//没有下一关卡了，说明
	if(level > levelCount)
	{
		//todo
		//MessageBox("当前已是最后一关，恭喜通关","恭喜");
		KnowledgeLayer*layer = KnowledgeLayer::create();
		this->addChild(layer,100);

		this->operateAllSchedulerAndActions(m_pTouchLayer,GameState::kOperatePause);
		this->operateAllSchedulerAndActions(m_pFishLayer,GameState::kOperatePause);
		this->operateAllSchedulerAndActions(m_pHelpLayer,GameState::kOperatePause);
		this->unscheduleUpdate();
	}
	else
	{
		//设置关卡
		m_nCurLevel = level;
		//重置
		DynamicData::getInstance()->clean();
		m_pPanelLayer->clean();

		m_pFishLayer->reset();

		std::string levelStr = StringUtils::format("level/level%d.lua",m_nCurLevel);
		this->loadLevel(levelStr);

		m_pPanelLayer->initWithTimes();
		m_pPanelLayer->initWithNeedfulFishes();
		//恢复
		this->operateAllSchedulerAndActions(m_pTouchLayer,GameState::kOperateResume);
		this->operateAllSchedulerAndActions(m_pFishLayer,GameState::kOperateResume);
		this->operateAllSchedulerAndActions(m_pHelpLayer,GameState::kOperateResume);

		this->scheduleUpdate();
	}
}
void GameScene::showQuestionLayer()
{
	//判断剩余回答问题次数
	auto questionTimes = DynamicData::getInstance()->getAnswerTimes();
	if(questionTimes <= 0)
	{
		auto valueMap = FileUtils::getInstance()->getValueMapFromFile("strings.xml");
		Toast::makeText(this,valueMap.at("str4").asString(),3.f);
	}
	else
	{
		auto pQuestionLayer = QuestionLayer::create();
		this->addChild(pQuestionLayer);
	}
}
void GameScene::turnToLevelLayer()
{
	//做基本的清除操作
	Director::getInstance()->replaceScene(LevelLayer::createScene());
}
void GameScene::operateAllSchedulerAndActions(Node*node,int flag)
{
	if(node->isRunning())
	{
		switch(flag)
		{
		case GameState::kOperateResume:
			node->resumeSchedulerAndActions();
			break;
		case GameState::kOperatePause:
			node->pauseSchedulerAndActions();
			break;
		}
		//迭代孩子
		auto children = node->getChildren();
		for(auto child:children)
		{
			this->operateAllSchedulerAndActions(child,flag);
		}
	}
}