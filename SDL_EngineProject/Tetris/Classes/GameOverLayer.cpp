#include "GameOverLayer.h"
GameOverLayer::GameOverLayer()
	:m_pDelegate(nullptr),m_pMenu(nullptr)
{
}
GameOverLayer::~GameOverLayer()
{
}
bool GameOverLayer::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//Ìí¼Ó±³¾°Í¼²ã
	LayerColor*layer = LayerColor::create(Color(0,0,0,128));
	this->addChild(layer);
	//Ìí¼ÓÓÎÏ·½áÊø
	Sprite*gameOver = Sprite::create("over.png");
	gameOver->setAnchorPoint(Point(0.5f,1.f));
	gameOver->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(gameOver);
	//Ìí¼Ó°´¼ü
	MenuItemSprite*retry = MenuItemSprite::create(Sprite::create("retry.png"),nullptr);
	retry->setCallback(SDL_CALLBACK_1(GameOverLayer::gameRetry,this));
	retry->setPosition(visibleSize.width/2,visibleSize.height/2);
	m_pMenu = Menu::create(retry,nullptr);
	this->addChild(m_pMenu);

	return true;
}
void GameOverLayer::show()
{
	this->setVisible(true);
	m_pMenu->setVisible(true);
}
void GameOverLayer::hide()
{
	this->setVisible(false);
	m_pMenu->setVisible(false);
}
void GameOverLayer::gameRetry(Object*sender)
{
	m_pDelegate->gameRetry();
}
void GameOverLayer::setDelegate(GameOverLayerDelegate*pDelegate)
{
	m_pDelegate = pDelegate;
}