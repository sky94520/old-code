#include "WinScene.h"
Scene*WinScene::createScene()
{
	auto scene = Scene::create();
	auto layer = WinScene::create();
	
	scene->addChild(layer);
	return scene;
}
bool WinScene::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Label*label = Label::create("you win!!!","Arial",40);
	label->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
	this->addChild(label);

	return true;
}