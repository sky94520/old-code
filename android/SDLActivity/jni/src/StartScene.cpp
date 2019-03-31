#include "StartScene.h"
StartScene::StartScene()
{
}
StartScene::~StartScene()
{
}
bool StartScene::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	Sprite*bg = Sprite::create("guide.jpg");
	bg->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(bg);
	//开始游戏按钮
	Sprite*playNormalSp = Sprite::create("button/play.png",Rect(0,0,400,100));
	Sprite*playSelectedSp = Sprite::create("button/play.png",Rect(400,0,400,100));
	/*playNormalSp->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(playNormalSp);*/
	MenuItemSprite*playBtn = MenuItemSprite::create(playNormalSp,playSelectedSp
		,nullptr,SDL_CALLBACK_1(StartScene::gameStart,this));
	playBtn->setPosition(visibleSize.width/2,visibleSize.height/2);
	Menu*menu = Menu::create(playBtn,NULL);
	//menu->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(menu);

	return true;
}
void StartScene::gameStart(Object*sender)
{
}
void StartScene::gameEnd(Object*sender)
{
}