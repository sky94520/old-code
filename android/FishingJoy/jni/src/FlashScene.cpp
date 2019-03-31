#include "FlashScene.h"
#include "StaticData.h"
#include "GB2ShapeCache-x.h"
#include "StartScene.h"
#include "B2EntityFactory.h"

FlashScene::FlashScene()
{
}

FlashScene::~FlashScene()
{
}

bool FlashScene::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//���ر���
	Sprite*bg = Sprite::create("logo.jpg");
	bg->setPosition(visibleSize.width/2,visibleSize.height/2);

	this->addChild(bg);
	//��һ֡����һЩ��̬��Դ
	this->scheduleOnce(SDL_CALLBACK_1(FlashScene::preload,this),"preload",0.1f);

	return true;
}

void FlashScene::preload(float dt)
{
	//����һЩ�޷��ŵ������̵߳���Դ
	StaticData::getInstance();
	PhysicalEngine::getInstance();
	//������ĸ���
	GB2ShapeCache::getInstance()->addShapesWithFile(STATIC_DATA_STRING("box2d_filepath"));
	B2EntityFactory::getInstance();
	//���뿪ʼ��Ϸ����
	StartScene*scene = StartScene::create();

	Director::getInstance()->replaceScene(scene);
}
