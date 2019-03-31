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
	//���һ�����ɫ�Ĳ�
	LayerColor*greyLayer = LayerColor::create(Color4B(25,25,25,25));
	this->addChild(greyLayer);
	auto listener = EventListenerTouchOneByOne::create();
	//��������onTouchBegan.�������ǿյ�
	listener->onTouchBegan = [](Touch*,Event*){return true;};
	//����touch
	listener->setSwallowTouches(false);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
	return true;
}