#include "StartMenuLayer.h"
StartMenuLayer::StartMenuLayer()
	:m_pDelegate(nullptr)
{
}
StartMenuLayer::~StartMenuLayer()
{
}
bool StartMenuLayer::init()
{
	//ui
	Node*layer = ui::UIWidgetManager::getInstance()->createWidgetsWithXml("scene/StartScene.xml");
	this->addChild(layer);
	//设置按钮回调函数
	Button*startBtn = layer->getChildByName<Button*>("start_btn");
	Button*shopBtn = layer->getChildByName<Button*>("shop_btn");
	Button*exitBtn = layer->getChildByName<Button*>("exit_btn");
	startBtn->addClickEventListener(SDL_CALLBACK_1(StartMenuLayer::gameStart,this));
	shopBtn->addClickEventListener(SDL_CALLBACK_1(StartMenuLayer::gotoShop,this));
	exitBtn->addClickEventListener(SDL_CALLBACK_1(StartMenuLayer::gameExit,this));
	return true;
}
void StartMenuLayer::gameStart(Object*sender)
{
	m_pDelegate->gameStart();
}
void StartMenuLayer::gotoShop(Object*sender)
{
	m_pDelegate->gotoShop();
}
void StartMenuLayer::gameExit(Object*sender)
{
	m_pDelegate->gameExit();
}
void StartMenuLayer::setDelegate(StartMenuLayerDelegate*pDelegate)
{
	m_pDelegate = pDelegate;
}