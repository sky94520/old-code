#include "MainLayer.h"
#include "ChooseLayer.h"

MainLayer::MainLayer()
	:m_pBackground(nullptr)
	,m_pFloor(nullptr)
	,m_pTitle(nullptr)
{
}
MainLayer::~MainLayer()
{
}
Scene*MainLayer::createScene()
{
	auto layer = MainLayer::create();
	auto scene = Scene::create();
	scene->addChild(layer);
	return scene;
}
bool MainLayer::init()
{
	TheDirector::getInstance()->getRenderer()->setRenderDrawColor(0,0xff,0xff,0xff);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//默认播放背景音乐
	SoundManager::getInstance()->playBackgroundMusic("sounds/playscene.mp3",-1);
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
	m_pTitle->setPositionX(visibleSize.width/2 - m_pTitle->getContentSize().width/2);
	this->addChild(m_pTitle);
	//按钮集合 start
	MenuItemImage*start = MenuItemImage::create("button/start.png","button/start_off.png");
	start->setCallback(SDL_CALLBACK_1(MainLayer::menuStartGame,this));
	Size size = start->getContentSize();
	//排行榜
	MenuItemImage*rank = MenuItemImage::create("button/rank.png","button/rank_off.png");
	rank->setPosition(size.width,0);
	//设置
	MenuItemImage*setting = MenuItemImage::create("button/set.png","button/set_off.png");
	setting->setPosition(0,size.width);
	//帮助
	MenuItemImage*help = MenuItemImage::create("button/help.png","button/help_off.png");
	help->setPosition(size.width,size.width);
	//关于
	MenuItemImage*about = MenuItemImage::create("button/about.png","button/about_off.png");
	about->setPosition(0,2 * size.width);
	//exit
	MenuItemImage*exit = MenuItemImage::create("button/exit.png","button/exit_off.png");
	exit->setPosition(size.width,2*size.width);
	exit->setCallback(SDL_CALLBACK_1(MainLayer::menuGameExit,this));

	Menu*menu = Menu::create(start,rank,setting,help,about,exit,nullptr);
	menu->setPosition(100,m_pTitle->getContentSize().height);
	this->addChild(menu);

	return true;
}
void MainLayer::menuStartGame(Object*obj)
{
	Director::getInstance()->replaceScene(ChooseLayer::createScene());
}
void MainLayer::update(float dt)
{
	printf("snake\n");
}
void MainLayer::menuGameExit(Object*)
{
	Director::getInstance()->setRunning(false);
}