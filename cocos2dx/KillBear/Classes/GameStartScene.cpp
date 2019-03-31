#include "GameStartScene.h"
#include "GameScene.h"
GameStartScene::GameStartScene()
{
}
GameStartScene::~GameStartScene()
{
}
Scene*GameStartScene::createScene()
{
	auto scene = Scene::create();
	scene->addChild(GameStartScene::create());
	return scene;
}
bool GameStartScene::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//±³¾°
	Sprite*bg = Sprite::create("GameStart.png");
	bg->setPosition(ccp(visibleSize.width/2,visibleSize.height/2)); 
	this->addChild(bg,0);
	//Ôö¼ÓMenuItem
	/*auto startBtn = MenuItemLabel::create(CCLabelBMFont::create("Start","main.fnt"),CC_CALLBACK_1(GameStartScene::gameStart,this));
	startBtn->setPosition(ccp(300,400));
	auto exitBtn = MenuItemLabel::create(CCLabelBMFont::create("Exit","main.fnt"),CC_CALLBACK_1(GameStartScene::gameEnd,this));
	exitBtn->setPosition(ccp(300,300));
	auto menu = Menu::create(startBtn,exitBtn,NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu,1);*/
	ui::Button*startBtn = ui::Button::create("button_normal.png","button_selected.png");
	startBtn->setTitleText("Start");
	startBtn->setTitleFontSize(30);
	startBtn->setPosition(ccp(300,400));
	this->addChild(startBtn);
	startBtn->addClickEventListener([&](Ref*pRef)
	{
		Director::getInstance()->replaceScene(GameScene::createScene());
	});
	ui::Button*exitBtn = ui::Button::create("button_normal.png","button_selected.png");
	exitBtn->setTitleText("Exit");
	exitBtn->setTitleFontSize(30);
	exitBtn->setPosition(ccp(300,300));
	this->addChild(exitBtn);
	exitBtn->addClickEventListener([&](Ref*pRef)
	{
		Director::getInstance()->end();
	});
	return true;
}
void GameStartScene::gameStart(Ref*pRef)
{
	Director::getInstance()->replaceScene(GameScene::createScene());
}
void GameStartScene::gameEnd(Ref*pRef)
{
	Director::getInstance()->end();
}