#include "LevelLayer.h"
#include "LuaEngine.h"
#include "DynamicData.h"
#include "GameScene.h"
#include "StartScene.h"

LevelLayer::LevelLayer()
{
}
LevelLayer::~LevelLayer()
{
}
Scene*LevelLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = LevelLayer::create();
	scene->addChild(layer);
	return scene;
}
bool LevelLayer::init()
{
	//���ؽű�
	LuaEngine::getInstance()->dofile("main.lua");
	//��ȡ�ܹؿ���Ŀ
	int levelCount = DynamicData::getInstance()->getLevelCount();
	if(levelCount < 0)
		return false;
	//���йؿ�ѡ����������
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite*bg = Sprite::create("level.jpg");
	bg->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(bg,-1);
	//ѭ����Ӱ�ť
	Point startPos = Point(80,visibleSize.height/2);
	for(int i=1;i <= levelCount;i++)
	{
		auto btnNormal = cocos2d::extension::Scale9Sprite::create("btn_normal.png",Rect(0,0,80,80),Rect(20,20,40,40));
		auto btnSelected = cocos2d::extension::Scale9Sprite::create("btn_selected.png",Rect(0,0,80,80),Rect(20,20,40,40));
		string str = Value(i).asString();
		Label*label = Label::create(str,"fonts/Marker Felt.ttf",30);
		//���ð�ť
		auto controlBtn = cocos2d::extension::ControlButton::create(label,btnNormal);
		controlBtn->setBackgroundSpriteForState(btnSelected,cocos2d::extension::Control::State::HIGH_LIGHTED);
		controlBtn->setTag(i);
		controlBtn->setPreferredSize(Size(80,80));
		this->addChild(controlBtn);
		//�ص����� ��������԰����ͷŽ��м���
		controlBtn->addTargetWithActionForControlEvents(this,
			cccontrol_selector(LevelLayer::btnCallback),
			cocos2d::extension::Control::EventType::TOUCH_UP_INSIDE);
		//���ð�ťλ��
		int row = i%MAX_BTN_NUMBER;
		int column = i/MAX_BTN_NUMBER;
		Point position = Point(row * 90,column * 100) + startPos;
		controlBtn->setPosition(position);
	}
	//��ӷ�����һ���˵���ť
	MenuItemImage*backBtn = MenuItemImage::create("botton_defray_back_001-hd.png","botton_defray_back_002-hd.png");
	backBtn->setCallback(CC_CALLBACK_1(LevelLayer::returnToStartScene,this));
	Size backBtnSize = backBtn->getContentSize();
	backBtn->setPosition(visibleSize.width/2-backBtnSize.width/2,visibleSize.height/2 - backBtnSize.height/2);

	Menu*menu = Menu::create(backBtn,nullptr);
	this->addChild(menu);

	return true;
}
void LevelLayer::btnCallback(Ref*sender,cocos2d::extension::Control::EventType eventType)
{
	Node* node = dynamic_cast<Node*>(sender);
	int i = node->getTag();
	
	//ת����Ϸ����
	Director::getInstance()->replaceScene(GameScene::create(i));
}
void LevelLayer::returnToStartScene(Ref*sender)
{
	Director::getInstance()->replaceScene(StartScene::create());
}