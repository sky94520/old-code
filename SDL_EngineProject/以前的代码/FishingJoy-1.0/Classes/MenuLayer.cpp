#include "MenuLayer.h"
#include "StartScene.h"
MenuLayer::MenuLayer()
	:m_pDelegate(nullptr)
{
}
MenuLayer::~MenuLayer()
{
}
bool MenuLayer::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//添加灰度层
	LayerColor*layerColor = LayerColor::create(Color(0,0,0,128));
	this->addChild(layerColor,-1);
	//添加按钮
	auto continueBtn = MenuItemLabel::create(
		LabelTTF::createWithTTF("Continue","Resources/Marker Felt.ttf",25,Color(255,255,255))
		,SDL_CALLBACK_1(MenuLayer::continueCallback,this)
		);
	continueBtn->setPosition(visibleSize.width/2 - continueBtn->getContentSize().width,100);
	auto exitBtn = MenuItemLabel::create(
		LabelTTF::createWithTTF("Exit","Resources/Marker Felt.ttf",25,Color(255,255,255))
		,SDL_CALLBACK_1(MenuLayer::exitCallback,this));
	exitBtn->setPosition(visibleSize.width/2 - exitBtn->getContentSize().width,150);
	auto menu = Menu::create(continueBtn,exitBtn,nullptr);
	this->addChild(menu);

	return true;
}
void MenuLayer::setDelegate(MenuLayerDelegate*pDelegate)
{
	m_pDelegate = pDelegate;
}
void MenuLayer::continueCallback(Object*obj)
{
	m_pDelegate->resume();
}
void MenuLayer::exitCallback(Object*obj)
{
	//返回到开始界面
	Director::getInstance()->replaceScene(StartScene::create());
}