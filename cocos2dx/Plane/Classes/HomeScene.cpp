#include "HomeScene.h"
#include "SettingLayer.h"
#include "GameScene.h"
#include "GB2ShapeCache-x.h"
bool HomeScene::init()
{
	if(!Scene::init())
		return false;
	//�����Դ
	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("texture/home_texture.plist","texture/home_texture.png");
	cache->addSpriteFramesWithFile("texture/setting_texture.plist","texture/setting_texture.png");
	cache->addSpriteFramesWithFile("texture/gameplay_texture.plist","texture/gameplay_texture.png");
	cache->addSpriteFramesWithFile("texture/plane.plist","texture/plane.png");
	//����Physical Editor
	auto shapeCache = GB2ShapeCache::sharedGB2ShapeCache();
	shapeCache->addShapesWithFile("Plane.plist");

	Size visibleSize = Director::getInstance()->getVisibleSize();
	//���bg
	auto bg = TMXTiledMap::create("map/red_bg.tmx");
	this->addChild(bg);
	//���top
	auto top = Sprite::createWithSpriteFrameName("home-top.png");
	top->setPosition(ccp(visibleSize.width/2,visibleSize.height - top->getContentSize().height/2));
	this->addChild(top);

	auto end = Sprite::createWithSpriteFrameName("home-end.png");
	end->setPosition(ccp(visibleSize.width/2,top->getContentSize().height/2));
	this->addChild(end);
	//��ʼ�˵�
	auto startSpriteNormal = Sprite::createWithSpriteFrameName("home.button.start.png");
	auto startSpriteSelected = Sprite::createWithSpriteFrameName("home.button.start-on.png");
	auto startMenuItem = MenuItemSprite::create(startSpriteNormal,startSpriteSelected);
	startMenuItem->setCallback(CC_CALLBACK_1(HomeScene::menuItemCallback,this));
	startMenuItem->setTag(SceneType::kSceneType_Game);
	//���ò˵�
	auto settingSpriteNormal = Sprite::createWithSpriteFrameName("home.button.setting.png");
	auto settingSpriteSelected = Sprite::createWithSpriteFrameName("home.button.setting-on.png");
	auto settingMenuItem = MenuItemSprite::create(settingSpriteNormal,settingSpriteSelected);
	settingMenuItem->setCallback(CC_CALLBACK_1(HomeScene::menuItemCallback,this));
	settingMenuItem->setTag(SceneType::kSceneType_Setting);
	//�����˵�
	auto helpSpriteNormal = Sprite::createWithSpriteFrameName("home.button.help.png");
	auto helpSpriteSelected = Sprite::createWithSpriteFrameName("home.button.help-on.png");
	auto helpMenuItem = MenuItemSprite::create(helpSpriteNormal,helpSpriteSelected);
	helpMenuItem->setCallback(CC_CALLBACK_1(HomeScene::menuItemCallback,this));
	helpMenuItem->setTag(SceneType::kSceneType_Help);

	auto menu = Menu::create(startMenuItem,settingMenuItem,helpMenuItem,nullptr);
	menu->setPosition(ccp(visibleSize.width/2,visibleSize.height/2));
	menu->alignItemsVerticallyWithPadding(12);
	this->addChild(menu);
	return true;
}
void HomeScene::menuItemCallback(Ref*sender)
{
	MenuItem*item = static_cast<MenuItem*>(sender);
	//��ʼ��Ϸ
	if(item->getTag() == SceneType::kSceneType_Game)
	{
		Director::getInstance()->pushScene(GameScene::create());
	}
	//���ò˵�
	else if(item->getTag() == SceneType::kSceneType_Setting)
	{
		Director::getInstance()->pushScene(SettingLayer::createScene());
	}
	//�����˵�
	else if(item->getTag() == SceneType::kSceneType_Help)
	{

	}
}