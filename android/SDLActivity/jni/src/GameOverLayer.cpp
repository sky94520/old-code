#include "GameOverLayer.h"
#include "DynamicData.h"

GameOverLayer::GameOverLayer()
	:m_pDelegate(nullptr)
{
}
GameOverLayer::~GameOverLayer()
{
}
bool GameOverLayer::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//添加一个半灰色背景
	LayerColor*bg = LayerColor::create(Color(0,0,0,128));
	this->addChild(bg);
	//添加分数信息
	LabelAtlas*scoreLabel = LabelAtlas::create("Game Over","lazyfont.png",39,55,0);
	scoreLabel->setColorKey(0,255,255);
	scoreLabel->setFontKerning(0.5f);
	scoreLabel->setPosition(visibleSize.width/2 - scoreLabel->getContentSize().width/2,visibleSize.height/2);
	this->addChild(scoreLabel);
	//添加重新开始按钮
	MenuItemLabel*restartBtn = MenuItemLabel::create(LabelTTF::createWithTTF("RESTART","fonts/Marker Felt.ttf"));
	restartBtn->setCallback(SDL_CALLBACK_1(GameOverLayer::gameRestart,this));
	restartBtn->setPosition(visibleSize.width/2 - restartBtn->getContentSize().width/2,visibleSize.height/2 + scoreLabel->getContentSize().height);

	auto menu = Menu::create(restartBtn,nullptr);
	this->addChild(menu);

	return true;
}
void GameOverLayer::setDelegate(GameOverDelegate*pDelegate)
{
	m_pDelegate = pDelegate;
}
void GameOverLayer::gameRestart(Object*sender)
{
	m_pDelegate->gameRestart();
}