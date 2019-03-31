#include "GameOverLayer.h"
#include "Entity.h"
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
	//创建灰色背景
	LayerColor*layer = LayerColor::create(Color4B(0,0,0,128));
	this->addChild(layer);

	Sprite*gameOver = Sprite::createWithSpriteFrameName("gameover0.png");
	gameOver->setAnchorPoint(Point(0.5f,1.f));
	gameOver->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(gameOver);

	Animate*animate = Entity::createAnimate("gameover%d.png",0,1,0.5f,-1);
	gameOver->runAction(animate);
	//创建按钮
	Sprite*restartNormal = Sprite::create("button/restart.png",Rect(0,0,200,80));
	Sprite*restartSelected = Sprite::create("button/restart.png",Rect(200,0,200,80));
	MenuItem*restartBtn = MenuItemSprite::create(restartNormal,restartSelected);
	restartBtn->setPosition(visibleSize.width/2,visibleSize.height/3*2);

	restartBtn->setCallback(SDL_CALLBACK_1(GameOverLayer::gameRestart,this));

	Menu*menu = Menu::create(restartBtn,NULL);
	this->addChild(menu);
	return true;
}
void GameOverLayer::gameRestart(Object*sender)
{
	m_pDelegate->gameRestart();
}
void GameOverLayer::setDelegate(GameOverDelegate*pDelegate)
{
	m_pDelegate = pDelegate;
}