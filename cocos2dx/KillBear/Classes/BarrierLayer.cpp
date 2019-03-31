#include "BarrierLayer.h"
BarrierLayer::BarrierLayer()
{
}
BarrierLayer::~BarrierLayer()
{
}
bool BarrierLayer::init()
{
	if(!Layer::init())
		return false;
	//添加一个半灰色的层
	LayerColor*greyLayer = LayerColor::create(Color4B(25,25,25,25));
	this->addChild(greyLayer);
	auto listener = EventListenerTouchOneByOne::create();
	//必须得添加onTouchBegan.就算它是空的
	listener->onTouchBegan = [](Touch*,Event*){return true;};
	//阻塞touch
	listener->setSwallowTouches(false);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
	return true;
}