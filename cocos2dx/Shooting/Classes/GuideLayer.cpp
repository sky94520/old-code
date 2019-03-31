#include "GuideLayer.h"

GuideLayer::GuideLayer()
{
	defaultColor = Color4B::Color4B(0x00,0x00,0x00,0xc0);
}
GuideLayer::~GuideLayer()
{}
bool GuideLayer::init()
{
	if(!Node::init())
		return false;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	//创建不可视区域
	area1 = LayerColor::create(defaultColor,visibleSize.width,visibleSize.height/4);
	area1->setAnchorPoint(Point(0,0));
	area1->setPosition(Point(0,0));

	area2 = LayerColor::create(defaultColor,visibleSize.width,visibleSize.height/4 * 3);
	area2->setAnchorPoint(Point(0,0));
	area2->setPosition(Point(0,visibleSize.height/4 * 3));

	area3 = LayerColor::create(defaultColor,visibleSize.width/4,visibleSize.height/2);
	area3->setAnchorPoint(Point(0,0));
	area3->setPosition(Point(0,visibleSize.height/4));

	area4 = LayerColor::create(defaultColor,visibleSize.width/4,visibleSize.height/2);
	area4->setAnchorPoint(Point(0,0));
	area4->setPosition(Point(visibleSize.width/4*3,visibleSize.height/4));
	//添加子节点
	this->addChild(area1);
	this->addChild(area2);
	this->addChild(area3);
	this->addChild(area4);

	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GuideLayer::onTouchBegan,this);
/*	listener->onTouchBegan = [&](Touch*touch,Event*event){
	
		Point pos = Director::getInstance()->convertToGL(touch->getLocationInView());
		Rect rect = Rect(visibleSize.width/4,visibleSize.height/4,visibleSize.width/4*3,visibleSize.height/4*3);
		listener->setSwallowTouches(false);
		//和返回值有关系，如果返回true，则触屏向下传递
		//返回false，不向下传递
		if(rect.containsPoint(pos))
			return false;
		else
		{
			listener->setSwallowTouches(true);
			return true;
		}
	};*/
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);

	return true;
}
bool GuideLayer::onTouchBegan(Touch*touch,Event*event)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
		Point pos = Director::getInstance()->convertToGL(touch->getLocationInView());
		Rect rect = Rect(visibleSize.width/4,visibleSize.height/4,visibleSize.width/4*3,visibleSize.height/4*3);
		listener->setSwallowTouches(false);
		//和返回值有关系，如果返回true，则触屏向下传递
		//返回false，不向下传递
		if(rect.containsPoint(pos))
			return false;
		else
		{
			listener->setSwallowTouches(true);
			return true;
		}
}

