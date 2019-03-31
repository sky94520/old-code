#include "SettingLayer.h"
#include "MyUtility.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
SettingLayer::SettingLayer()
	:m_bMusicPlaying(true),m_bEffectPlaying(true)//todo
{
}
bool SettingLayer::init()
{
	
	BaseLayer::init();
	//ÉèÖÃ
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto setting = Sprite::createWithSpriteFrameName("setting-top.png");
	setting->setPosition(ccp(visibleSize.width/2,
		visibleSize.height - setting->getContentSize().height/2));
	this->addChild(setting);

	//ÒôÀÖÒôÐ§ Í¼Æ¬
	auto musicOnItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("setting.check-on.png"),nullptr);
	auto musicOffItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("setting.check-off.png"),nullptr);

	auto effectOnItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("setting.check-on.png"),nullptr);
	auto effectOffItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("setting.check-off.png"),nullptr);

	auto musicToggle = MenuItemToggle::createWithCallback(
		CC_CALLBACK_1(SettingLayer::musicToggle,this),musicOnItem,musicOffItem,nullptr);

	auto effectToggle = MenuItemToggle::createWithCallback(
		CC_CALLBACK_1(SettingLayer::effectToggle,this),effectOnItem,effectOffItem,nullptr);
	Menu*menu = Menu::create(musicToggle,effectToggle,nullptr);
	menu->setPosition(ccp(visibleSize.width/2,visibleSize.height/2) + ccp(70, 50));
	menu->alignItemsVerticallyWithPadding(40);
	this->addChild(menu);
	//ÒôÀÖ
	auto text1 = MyUtility::gbk_to_utf8("ÒôÀÖ");
	Label*musicLabel = Label::createWithTTF(text1,"fonts/hanyi.ttf",40,Size(200,200));
	musicLabel->setColor(Color3B(14,83,204));
	musicLabel->setPosition(menu->getPosition() - Vec2(100, 20));
	this->addChild(musicLabel);
	//ÒôÐ§
	auto text2 = MyUtility::gbk_to_utf8("ÒôÐ§");
	Label*effectLabel = Label::createWithTTF(text2,"fonts/hanyi.ttf",40,Size(200,200));
	effectLabel->setColor(Color3B(14,83,204));
	effectLabel->setPosition(menu->getPosition() - Vec2(100, 140));
	this->addChild(effectLabel);
	return true;
}
Scene*SettingLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = SettingLayer::create();
	scene->addChild(layer);
	return scene;
}
void SettingLayer::menuBackCallback(Ref*ref)
{
	//todo
	if(m_bMusicPlaying)
		SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/home_bg.mp3",true);
	else
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();

	BaseLayer::menuBackCallback(ref);
}
void SettingLayer::musicToggle(Ref*)
{
	m_bMusicPlaying = !m_bMusicPlaying;
}
void SettingLayer::effectToggle(Ref*)
{
	m_bEffectPlaying = !m_bEffectPlaying;
}