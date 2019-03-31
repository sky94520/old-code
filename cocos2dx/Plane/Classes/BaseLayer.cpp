#include "BaseLayer.h"
bool BaseLayer::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	//±³¾°
	auto bg = TMXTiledMap::create("map/red_bg.tmx");
	this->addChild(bg);
	//ÑÛ¾¦¾«Áé
	auto glassSprite = Sprite::createWithSpriteFrameName("setting.glasses.png");
	glassSprite->setPosition(ccp(visibleSize.width-glassSprite->getContentSize().width/2,300));
	this->addChild(glassSprite);
	//ÊÖÌ×¾«Áé
	auto handSprite = Sprite::createWithSpriteFrameName("setting.hand.png");
	handSprite->setPosition(ccp(handSprite->getContentSize().width/2
		,handSprite->getContentSize().height/2));
	this->addChild(handSprite);
	//ok²Ëµ¥
	auto okBtn = MenuItemSprite::create(
		Sprite::createWithSpriteFrameName("setting.button.ok.png"),
		Sprite::createWithSpriteFrameName("setting.button.ok-on.png"),
		CC_CALLBACK_1(BaseLayer::menuBackCallback,this));
	auto menu = Menu::create(okBtn,nullptr);
	menu->setPosition(ccp(visibleSize.width - okBtn->getContentSize().width/2,okBtn->getContentSize().height/2));
	this->addChild(menu);
	return true;
}
Scene*BaseLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = BaseLayer::create();
	scene->addChild(layer);
	return scene;
}
void BaseLayer::menuBackCallback(Ref*)
{
	Director::getInstance()->popScene();
}