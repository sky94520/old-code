#include "GameStart.h"
#include "SceneManager.h"
GameStart::GameStart()
{
}
GameStart::~GameStart()
{
}
Scene*GameStart::createScene()
{
	auto scene = Scene::create();
	auto layer = GameStart::create();
	scene->addChild(layer);
	return scene;
}
bool GameStart::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	MenuItemLabel*pGameStart = MenuItemLabel::create(Label::create("Game Start","Marker Felt",30),CC_CALLBACK_1(GameStart::gameStart,this));
	MenuItemLabel*pEdit = MenuItemLabel::create(Label::create("Edit","Marker Felt",30),CC_CALLBACK_1(GameStart::edit,this));
	Menu*menu = Menu::create(pGameStart,pEdit,NULL);
	menu->setPosition(visibleSize/2);
	//设置菜单项竖直排列
	menu->alignItemsVertically();
	this->addChild(menu);
	return true;
}
void GameStart::gameStart(Ref*pRef)
{
	SceneManager::getInstance()->changeScene(EnumSceneType::en_TollgateScene);
}
void GameStart::edit(Ref*pRef)
{
	SceneManager::getInstance()->changeScene(EnumSceneType::en_TollgateEditorScene);
}