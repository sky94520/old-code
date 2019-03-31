#include "BeginScene.h"
#include "GameScene.h"

#include "CsvUtil.h"

Scene*BeginScene::createScene()
{
	auto scene = Scene::create();
	auto layer = BeginScene::create();

	scene->addChild(layer);

	return scene;
}
bool BeginScene::init()
{
	if(!Layer::init())
		return false;
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto UI = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("Start/FlyPlane_1.ExportJson");

	UI->setAnchorPoint(Point(0,0));
	this->addChild(UI,6);

	//get button
	Button*beginBtn = (Button*)Helper::seekWidgetByName(UI,"BeginBtn");
	beginBtn->addTouchEventListener(this,toucheventselector(BeginScene::clickBeginBtn));

	Button*modeBtn = (Button*)Helper::seekWidgetByName(UI,"ModeBtn");
	modeBtn->addTouchEventListener(this,toucheventselector(BeginScene::clickModeBtn));

	Button*aboutBtn = (Button*)Helper::seekWidgetByName(UI,"AboutBtn");
	aboutBtn->addTouchEventListener(this,toucheventselector(BeginScene::clickAboutBtn));

	Button*exitBtn = (Button*)Helper::seekWidgetByName(UI,"ExitBtn");
	exitBtn->addTouchEventListener(this,toucheventselector(BeginScene::clickExitBtn));

	Sprite*bg = Sprite::create("bg.png");
	bg->setAnchorPoint(Point(0,0));
	bg->setPosition(Vec2::ZERO);
	this->addChild(bg,-6);

/*	const char*sPath = "Plane.csv";
	CsvUtil::getInstance()->loadFile(sPath);
	for(int i = 0;i < 4;i++)
	{
	Value value = CsvUtil::getInstance()->getValue(2,i,sPath);
	log(value.asString().c_str());
	}
	*/
	return true;
}
void BeginScene::clickBeginBtn(Ref*,TouchEventType type)
{

	switch(type)
	{
	case TouchEventType::TOUCH_EVENT_BEGAN : 
		break;
	case TouchEventType::TOUCH_EVENT_MOVED : 
		break;
	case TouchEventType::TOUCH_EVENT_ENDED :
		Director::getInstance()->replaceScene(TransitionSlideInL::create(3.0f,GameScene::createScene()));
		break;
	case TouchEventType::TOUCH_EVENT_CANCELED :
		break;
	}
	
}
void BeginScene::clickModeBtn(Ref*,TouchEventType type)
{
//	log("click mode");
		switch(type)
	{
	case TouchEventType::TOUCH_EVENT_BEGAN : 
		break;
	case TouchEventType::TOUCH_EVENT_MOVED : 
		break;
	case TouchEventType::TOUCH_EVENT_ENDED :
		log("click mode");
		break;
	case TouchEventType::TOUCH_EVENT_CANCELED :
		break;
	}
}
void BeginScene::clickAboutBtn(Ref*,TouchEventType type)
{
//	log("click about");
		switch(type)
	{
	case TouchEventType::TOUCH_EVENT_BEGAN : 
		break;
	case TouchEventType::TOUCH_EVENT_MOVED : 
		break;
	case TouchEventType::TOUCH_EVENT_ENDED :

		break;
	case TouchEventType::TOUCH_EVENT_CANCELED :
		break;
	}
}
void BeginScene::clickExitBtn(Ref*,TouchEventType type)
{
//	log("click exit");
		switch(type)
	{
	case TouchEventType::TOUCH_EVENT_BEGAN : 
		break;
	case TouchEventType::TOUCH_EVENT_MOVED : 
		break;
	case TouchEventType::TOUCH_EVENT_ENDED :
		#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
		MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
		return;
#endif
		Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

		break;
	case TouchEventType::TOUCH_EVENT_CANCELED :
		break;
	}
}