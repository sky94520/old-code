#include "GamePause.h"
#include "ui/CocosGUI.h"
#include "BarrierLayer.h"
#include "GameScene.h"
#include "GameStartScene.h"
GamePause::GamePause()
{
}
GamePause::~GamePause()
{
}
bool GamePause::init()
{
	if(!Layer::init())
		return false;
	//添加灰色
	this->addChild(BarrierLayer::create(),0);

	ui::Button*continueBtn = ui::Button::create("button_normal.png","button_selected.png");
	continueBtn->setTitleText("continue");
	continueBtn->setTitleFontSize(30);
	continueBtn->setPosition(ccp(300,400));
	this->addChild(continueBtn);
	continueBtn->addClickEventListener([&](Ref*pRef)
	{
		//btn获得父亲GamePause然后从父亲这删除
		getParent()->removeChild(this);
		Director::getInstance()->resume();
	});
	ui::Button*restartBtn = ui::Button::create("button_normal.png","button_selected.png");
	restartBtn->setTitleText("restart");
	restartBtn->setTitleFontSize(30);
	restartBtn->setPosition(ccp(300,300));
	this->addChild(restartBtn);
	restartBtn->addClickEventListener([](Ref*pRef)
	{
		Director::getInstance()->resume();
		Director::getInstance()->replaceScene(GameScene::createScene());
	});
	ui::Button*exitBtn = ui::Button::create("button_normal.png","button_selected.png");
	exitBtn->setTitleText("exit");
	exitBtn->setTitleFontSize(30);
	exitBtn->setPosition(ccp(300,200));
	this->addChild(exitBtn);
	exitBtn->addClickEventListener([&](Ref*pRef)
	{
		Director::getInstance()->resume();
		Director::getInstance()->replaceScene(
			GameStartScene::createScene());
	});

	//MenuItemSprite
	//MenuItemImage*continueBtn = MenuItemImage::create(
	return true;
}