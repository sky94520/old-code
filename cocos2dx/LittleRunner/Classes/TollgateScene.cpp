#include "TollgateScene.h"
#include "MonsterManager.h"

Scene*TollgateScene::createScene()
{
	auto scene = Scene::create();
	auto layer = TollgateScene::create();
	scene->addChild(layer);
	return scene;
}
bool TollgateScene::init()
{
	if(!Layer::init())
		return false;
	m_iScore = 0;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//游戏标题图片
	Sprite*titleSprite = Sprite::create("title.png");
	titleSprite->setPosition(Point(visibleSize.width/2,visibleSize.height-50));
	this->addChild(titleSprite,2);

	//创建zhujue
	m_player =Player::create();
	m_player->bindSprite(Sprite::create("sprite.png"));
	m_player->setPosition(Point(m_player->getContentSize().width,50));
	this->addChild(m_player,3);
	//创建怪物
	MonsterManager*monsterMgr = MonsterManager::create();
	this->addChild(monsterMgr,4);
	monsterMgr->bindPlayer(m_player);
	
	//初始化背景
	initBG();

	loadUI();

	this->scheduleUpdate();

	return true;
}
void TollgateScene::initBG()
{
	
	Size visibleSize= Director::getInstance()->getVisibleSize();

	m_bgSprite1 = Sprite::create("tollgateBG.jpg");
	m_bgSprite1->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
	this->addChild(m_bgSprite1,0);

	m_bgSprite2 = Sprite::create("tollgateBG.jpg");
	m_bgSprite2->setPosition(Point(visibleSize.width+visibleSize.width/2,visibleSize.height/2));
	m_bgSprite2->setFlippedX(true);
	this->addChild(m_bgSprite2,0);
	
}
void TollgateScene::update(float delta)
{
	int posX1 = m_bgSprite1->getPositionX();
	int posX2 = m_bgSprite2->getPositionX();

	int iSpeed = 2;
	posX1 -= iSpeed;
	posX2 -= iSpeed;

	Size mapSize = m_bgSprite1->getContentSize();

	if (posX1 <= -mapSize.width/2)
		posX1 = mapSize.width + mapSize.width/2;

	if (posX2 <= -mapSize.width/2)
		posX2 = mapSize.width + mapSize.width/2;

	m_bgSprite1->setPositionX(posX1);
	m_bgSprite2->setPositionX(posX2);

	m_iScore += 1;
	m_scoreLab->setText(Value(m_iScore).asString());
	m_hpBar->setPercent(m_player->getiHP()/1000.0f*100);

}
void TollgateScene::loadUI()
{
	auto UI = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("LittleRunnerUI/LittleRunnerUI_1.ExportJson");
	this->addChild(UI);

	//
	auto jumpBtn = (Button*)Helper::seekWidgetByName(UI,"JumpBtn");
	m_scoreLab = (Text*)Helper::seekWidgetByName(UI,"scoreLab");
	m_hpBar = (LoadingBar*)Helper::seekWidgetByName(UI,"hpProgress");

	jumpBtn->addTouchEventListener(this,toucheventselector(TollgateScene::jumpEvent));

}
void TollgateScene::jumpEvent(Ref*,TouchEventType type)
{
	switch(type)
	{
	case TouchEventType::TOUCH_EVENT_ENDED:
		m_player->jump();
		break;
	}
}
