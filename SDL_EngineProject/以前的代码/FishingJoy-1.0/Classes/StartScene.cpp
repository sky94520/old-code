#include "StartScene.h"
#include "GameScene.h"
#include "LoadingLayer.h"
StartScene::StartScene()
{
}
StartScene::~StartScene()
{
}
bool StartScene::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//����ͼƬ��Դ
	Director::getInstance()->getSpriteFrameCache()->addSpriteFramesWithFile("start_resources.xml","start_resources.png");
	TheDirector::getInstance()->getRenderer()->setRenderDrawColor(0x00,0xff,0xff,0xff);
	//��ʼ������
	Sprite* pBackground = Sprite::createWithSpriteFrameName("start_bg.png");
	this->addChild(pBackground,-1);
	//��ӱ�����
	Sprite*pTitle = Sprite::createWithSpriteFrameName("title.png");
	Size titleSize = pTitle->getContentSize();
	//���õ�����λ��
	pTitle->setPosition((visibleSize.width-titleSize.width)/2,0);
	this->addChild(pTitle);
	//��ʼ��ť
	MenuItemSprite*startBtn = MenuItemSprite::create(
		Sprite::createWithSpriteFrameName("start_normal.png")
		,Sprite::createWithSpriteFrameName("start_selected.png")
		,Sprite::createWithSpriteFrameName("start_selected.png")
		,SDL_CALLBACK_1(StartScene::startGame,this));

	Size startBtnSize = startBtn->getContentSize();
	startBtn->setPosition(visibleSize.width/2  - startBtnSize.width/2,visibleSize.height/2);
	auto menu = Menu::create(startBtn,nullptr);
	this->addChild(menu);
	return true;
}
void StartScene::startGame(Object*obj)
{
	/**/
	Director::getInstance()->replaceScene(LoadingLayer::createScene());
}