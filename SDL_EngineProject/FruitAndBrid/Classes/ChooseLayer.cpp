#include "ChooseLayer.h"
#include "MainLayer.h"
#include "GameScene.h"

ChooseLayer::ChooseLayer()
	:m_pBackground(nullptr),
	m_pFloor(nullptr),
	m_pTitle(nullptr)
{
}
ChooseLayer::~ChooseLayer()
{
}
Scene*ChooseLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = ChooseLayer::create();
	scene->addChild(layer);
	return scene;
}
bool ChooseLayer::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//背景
	int i = rand();
	if(i % 2 == 0)
		m_pBackground = Sprite::create("pic/morning.png");
	else
		m_pBackground = Sprite::create("pic/night.png");
	this->addChild(m_pBackground,-1);
	//地面精灵
	m_pFloor = Sprite::create("pic/floor.png");
	Size floorSize = m_pFloor->getContentSize();
	m_pFloor->setPositionY(visibleSize.height - floorSize.height);
	this->addChild(m_pFloor);
	//标题
	m_pTitle = Sprite::create("pic/title.png");
	Size titleSize = m_pTitle->getContentSize();
	m_pTitle->setPositionX(visibleSize.width/2 - titleSize.width/2);
	this->addChild(m_pTitle,-1);
	//进击的小鸟
	MenuItemImage*bird = MenuItemImage::create("button/Bird.png","button/Bird_off.png");
	bird->setCallback(SDL_CALLBACK_1(ChooseLayer::startBirdGame,this));
	bird->setPosition(0,titleSize.height);
	//fruit
	MenuItemImage*fruit = MenuItemImage::create("button/Fruit.png","button/Fruit_off.png");
	Size fruitSize = fruit->getContentSize();
	fruit->setPosition(visibleSize.width - fruitSize.width,bird->getPosition().y + fruitSize.height);
	//主菜单
	MenuItemImage*menuItem = MenuItemImage::create("button/menu.png","button/menu_off.png");
	menuItem->setPosition(20,visibleSize.height - fruitSize.height);
	menuItem->setCallback(SDL_CALLBACK_1(ChooseLayer::backToMainLayer,this));
	auto menu = Menu::create(bird,fruit,menuItem,nullptr);

	this->addChild(menu);
	
	return true;
}
void ChooseLayer::startBirdGame(Object*)
{
	Director::getInstance()->replaceScene(GameScene::create());
}
void ChooseLayer::backToMainLayer(Object*)
{
	Director::getInstance()->replaceScene(MainLayer::createScene());
}