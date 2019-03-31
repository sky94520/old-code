#include "GameScene.h"
#include "PlaneAction.h"
#include "TouchController.h"
#include "MonsterManager.h"

#include "SaveData.h"



Scene*GameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameScene::create();

	scene->addChild(layer);

	return scene;
}
bool GameScene::init()
{
	if(!Layer::init())
		return false;
	
	m_cloud1 = Sprite::create("cloud1.png");
	m_cloud1->setPosition(Point(0,0));
	m_cloud2 = Sprite::create("cloud2.png");
	m_cloud2->setPosition(Point(0,0));
	this->addChild(m_cloud1,50);
	this->addChild(m_cloud2,50);

	m_cloudSprite = m_cloud1;
	m_cloudSprite->retain();

	this->scheduleUpdate();
	//背景
	initBG();


	//主角控制器
	TouchController*touchController = TouchController::create();
	
	this->addChild(touchController);
	//主角
	m_player = Player::create();
	m_player->bindSprite(Sprite::create("player1.png"));
	m_player->run(PlaneAction::getInstance()->getActionByString(std::string("player")));
	m_player->setPosition(Point(200,200));
	this->addChild(m_player);

	m_player->setTouchController(touchController);

	touchController->handleTouchEvent();

	//加入主角子弹
	bulletManager = BulletManager::create();
	this->addChild(bulletManager);

	this->schedule(schedule_selector(GameScene::bulletMgrUpdate),0.5f);
	//加入怪物
	MonsterManager*monsterManager = MonsterManager::create();
	this->addChild(monsterManager);
	monsterManager->bindPlayer(m_player);

	monsterManager->bindBulletMgr(bulletManager);

	//分数控件
	auto gameDateUI = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("GameData/GameData_1.ExportJson");
	/*gameDateUI->setAnchorPoint(Point(0,1.0));
	gameDateUI->setPosition(Point(0,0));
	*/
	this->addChild(gameDateUI);
	gameDateUI->setTouchEnabled(false);
	//获取控件对象
	m_scoreUI = (cocos2d::ui::Text*)cocos2d::ui::Helper::seekWidgetByName(gameDateUI,"Score");

	return true;
}
GameScene::GameScene()
{
	m_cloudExist = false;
}
GameScene::~GameScene()
{
}

void GameScene::initBG()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	m_bgSprite1 = Sprite::create("bg.png");
	m_bgSprite1->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
	this->addChild(m_bgSprite1);

	m_bgSprite2 = Sprite::create("bg.png");
	m_bgSprite2->setPosition(Point(visibleSize.width/2,visibleSize.height/2 * 3));
	this->addChild(m_bgSprite2);
}
void GameScene::update(float dt)
{
	int pos1 = m_bgSprite1->getPositionY();
	int pos2 = m_bgSprite2->getPositionY();

	int speed = 1;
	Size mapSize = m_bgSprite1->getContentSize();

	pos1 -= speed;
	pos2 -= speed;

	if(pos1 <= -mapSize.height/2)
		pos1 = mapSize.height/2 * 3;
	if(pos2 <= -mapSize.height/2)
		pos2 = mapSize.height/2 * 3;

	m_bgSprite1->setPositionY(pos1);
	m_bgSprite2->setPositionY(pos2);



	getCloud();
	int posCloud = m_cloudSprite->getPositionY();

	posCloud -= 4;

	if(posCloud <= 0)
		m_cloudExist = false;


	m_cloudSprite->setPositionY(posCloud);
	//分数增加
	m_scoreUI->setText(Value(SaveData::getInstance()->getScore()).asString());
	//log(Value(SaveData::getInstance()->getScore()).asString().c_str());
}
void GameScene::getCloud()
{
	if(m_cloudExist == false)
	{
		m_cloudExist = true;

		Size visibleSize = Director::getInstance()->getVisibleSize();

		int randomX = CCRANDOM_0_1() * visibleSize.width;
		//获得大云
		if(CCRANDOM_0_1() <= 0.5f)
			m_cloudSprite = m_cloud1;
		//小云
		else
			m_cloudSprite = m_cloud2;

		m_cloudSprite->setPosition(Point(randomX,visibleSize.height));
	}
}
//每次都使一个子弹类活跃
void GameScene::bulletMgrUpdate(float dt)
{
	Point point = m_player->getPosition();
	Size playerSize = m_player->getContentSize();
	Point pos = Point(point.x,point.y + playerSize.height / 2 );

	bulletManager->addBullet(pos);
}