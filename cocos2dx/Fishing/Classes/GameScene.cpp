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
	/*û��Ҫ��������������ת��LevelLayerʱ��
	��Ϊ��LevelLayer::create()��purge,�ٴ�GameScene::create()
	���൱��main.lua��û�м��أ��Ӷ�����*/
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
	//������Դ
	auto spriteFrameCache = SpriteFrameCache::getInstance();
	spriteFrameCache->addSpriteFramesWithFile("fish.plist");
	//���ؽű�
	//LuaEngine::getInstance()->dofile("main.lua");
	//���õ�ǰ�ؿ�
	m_nCurLevel = level;
	std::string levelStr = StringUtils::format("level/level%d.lua",m_nCurLevel);
	this->loadLevel(levelStr);
	//�¼��ַ���
	m_pTouchLayer = TouchLayer::create();
	m_pTouchLayer->setDelegate(this);
	this->addChild(m_pTouchLayer);
	//������
	Size visibleSize = Director::getInstance()->getVisibleSize();

	Sprite*bg = Sprite::create("background.jpg");
	bg->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(bg,-1);
	//���������
	m_pHelpLayer = HelpLayer::create();
	m_pHelpLayer->setDelegate(this); 
	this->addChild(m_pHelpLayer);
	//����
	m_pPanelLayer = PanelLayer::create();
	m_pPanelLayer->setDelegate(this);
	this->addChild(m_pPanelLayer);
	//��Ϸ��
	m_pGameLayer = GameLayer::create();
	this->addChild(m_pGameLayer);
	//fish layer
	m_pFishLayer = FishLayer::create();
	this->addChild(m_pFishLayer);
	//��ͣ�� Ĭ�ϲ���ʾ
	m_pPauseLayer = PauseLayer::create();
	m_pPauseLayer->setVisible(false);
	m_pPauseLayer->setDelegate(this);

	m_pPanelLayer->initWithTimes();
	m_pPanelLayer->initWithNeedfulFishes();
	this->addChild(m_pPauseLayer);
	//ʧ�ܲ�
	m_pDefeatLayer = DefeatLayer::create();
	m_pDefeatLayer->setVisible(false);
	m_pDefeatLayer->setDelegate(this);
	this->addChild(m_pDefeatLayer);
	//�ɹ���
	m_pSuccessLayer = SuccessLayer::create();
	m_pSuccessLayer->setVisible(false);
	m_pSuccessLayer->setDelegate(this);
	this->addChild(m_pSuccessLayer);
	
	//����update
	this->scheduleUpdate();
	//�����ײ������
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
	//���ؽű�
	LuaEngine::getInstance()->dofile(filename);
	//��ȡ��������
	DynamicData::getInstance()->initlize();
	//��������ƫ�� ����x������y
	DynamicData::getInstance()->setOffsetRefraction(Point(-25,30));
}
void GameScene::shoot(const Point&targetPos)
{
	//�����ʱ��ʾ�������������
	if(m_pPanelLayer->isShowAllComp())
	{
		m_pPanelLayer->hideAllNeedfulFishesComp();
		m_pPanelLayer->setShowAllComp(false);
	}

	auto fork = m_pGameLayer->getFork();
	if(fork->isShooting())
		return;
	//��Сͼ����ʾ������й켣
	m_pHelpLayer->showHelpfulFork(targetPos);

	fork->setVisible(true);
	fork->shoot(targetPos);
	//���ٳ��ִ��� ͬʱ�жϲ����Ƿ�ʣ��
	auto defead = DynamicData::getInstance()->reduceAtkTimes();
	//����ʧ��
	if(defead == false)
	{
		//��Ϸ��ͣ
		this->operateAllSchedulerAndActions(m_pTouchLayer,GameState::kOperatePause);
		this->operateAllSchedulerAndActions(m_pFishLayer,GameState::kOperatePause);
		this->operateAllSchedulerAndActions(m_pHelpLayer,GameState::kOperatePause);
		this->unscheduleUpdate();
		//��ʾʧ�ܽ���
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
	//a ������� b���
	if((filterA.categoryBits == 0x02 && filterB.categoryBits == 0x04))
	{
		Fish*fish = static_cast<Fish*>(entity1);
		fish->runScaredAnimation();
	}
	//a ��� b�������
	else if(filterA.categoryBits == 0x04 && filterB.categoryBits == 0x02)
	{
			Fish*fish = static_cast<Fish*>(entity2);
			fish->runScaredAnimation();
	}
	//a �� b ���
	else if(filterA.categoryBits == 0x01 && filterB.categoryBits == 0x04)
	{
		Fork*fork = static_cast<Fork*>(entity2);
		//ֻ����������ڲ���ʱ�Ż������ײ�ж�
		if(fork->isShooting() == true)
		{
			Fish*fish = static_cast<Fish*>(entity1);
			fish->catched();
			//ץ������ж��Ƿ������������
			success = DynamicData::getInstance()->reduceFish(fish->getID());
		}
	}
	//a��� b��
	else if(filterA.categoryBits == 0x04 && filterB.categoryBits == 0x01)
	{
		Fork*fork = static_cast<Fork*>(entity1);
		//ֻ����������ڲ���ʱ�Ż������ײ�ж�
		if(fork->isShooting() == true)
		{
			Fish*fish = static_cast<Fish*>(entity2);
			fish->catched();
			success = DynamicData::getInstance()->reduceFish(fish->getID());
		}
	}
	//�ɹ�����
	if(success)
	{
		//��ͣ
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
	//������ ������
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
	//�Ƿ��������
	if(m_pPanelLayer->isClickedComponents(pos) == true)
	{
		//����Ѿ���ʾ������ ������ hide
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
	//��ʾ��ͣ����
	m_pPauseLayer->setVisible(true);
}
void GameScene::gameResume()
{
	this->operateAllSchedulerAndActions(m_pTouchLayer,GameState::kOperateResume);
	this->operateAllSchedulerAndActions(m_pFishLayer,GameState::kOperateResume);
	this->operateAllSchedulerAndActions(m_pHelpLayer,GameState::kOperateResume);

	this->scheduleUpdate();
	//�ر���ͣ����
	m_pPauseLayer->setVisible(false);
}
void GameScene::gameRestart()
{
	//�ָ�
	this->operateAllSchedulerAndActions(m_pTouchLayer,GameState::kOperateResume);
	this->operateAllSchedulerAndActions(m_pFishLayer,GameState::kOperateResume);
	this->operateAllSchedulerAndActions(m_pHelpLayer,GameState::kOperateResume);
	
	//���ù���������
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
	//�ж��Ƿ���һ�ؿ���
	int level = m_nCurLevel + 1;
	int levelCount = DynamicData::getInstance()->getLevelCount();
	//û����һ�ؿ��ˣ�˵��
	if(level > levelCount)
	{
		//todo
		//MessageBox("��ǰ�������һ�أ���ϲͨ��","��ϲ");
		KnowledgeLayer*layer = KnowledgeLayer::create();
		this->addChild(layer,100);

		this->operateAllSchedulerAndActions(m_pTouchLayer,GameState::kOperatePause);
		this->operateAllSchedulerAndActions(m_pFishLayer,GameState::kOperatePause);
		this->operateAllSchedulerAndActions(m_pHelpLayer,GameState::kOperatePause);
		this->unscheduleUpdate();
	}
	else
	{
		//���ùؿ�
		m_nCurLevel = level;
		//����
		DynamicData::getInstance()->clean();
		m_pPanelLayer->clean();

		m_pFishLayer->reset();

		std::string levelStr = StringUtils::format("level/level%d.lua",m_nCurLevel);
		this->loadLevel(levelStr);

		m_pPanelLayer->initWithTimes();
		m_pPanelLayer->initWithNeedfulFishes();
		//�ָ�
		this->operateAllSchedulerAndActions(m_pTouchLayer,GameState::kOperateResume);
		this->operateAllSchedulerAndActions(m_pFishLayer,GameState::kOperateResume);
		this->operateAllSchedulerAndActions(m_pHelpLayer,GameState::kOperateResume);

		this->scheduleUpdate();
	}
}
void GameScene::showQuestionLayer()
{
	//�ж�ʣ��ش��������
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
	//���������������
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
		//��������
		auto children = node->getChildren();
		for(auto child:children)
		{
			this->operateAllSchedulerAndActions(child,flag);
		}
	}
}