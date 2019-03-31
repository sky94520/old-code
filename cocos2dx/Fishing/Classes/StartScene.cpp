#include "StartScene.h"
#include "LevelLayer.h"
#include "AboutScene.h"

StartScene::StartScene()
{
}
StartScene::~StartScene()
{
}
bool StartScene::init()
{
	Node*startScene = CSLoader::createNode("start_res/MainScene.csb");
	this->addChild(startScene);
	//绑定函数
	//开始游戏按钮
	Widget*startBtn = static_cast<Widget*>(startScene->getChildByName("start_btn"));
	startBtn->addClickEventListener(CC_CALLBACK_1(StartScene::gameStart,this));
	//游戏帮助按钮
	Widget*helpBtn = static_cast<Widget*>(startScene->getChildByName("help_btn"));
	helpBtn->addClickEventListener(CC_CALLBACK_1(StartScene::gameHelpLayer,this));
	//游戏退出按钮
	Widget*exitBtn = static_cast<Widget*>(startScene->getChildByName("exit_btn"));
	exitBtn->addClickEventListener(CC_CALLBACK_1(StartScene::gameExit,this));
	return true;
}
void StartScene::gameStart(Ref*sender)
{
	Director::getInstance()->replaceScene(LevelLayer::createScene());
}
void StartScene::gameHelpLayer(Ref*sender)
{
	Director::getInstance()->replaceScene(AboutScene::create());
}
void StartScene::gameExit(Ref*sender)
{
	Director::getInstance()->end();
}