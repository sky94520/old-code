#include "TouchController.h"

bool TouchController::init()
{
	return true;
}
void TouchController::setTouchListener(TouchListener*iTouchListener)
{
	m_touchListener = iTouchListener;
}
void TouchController::handleTouchEvent()
{
	if(this->m_touchListener == NULL)
		return;
	Size visibleSize = Director::getInstance()->getVisibleSize();
//	log("handleTouchEvent");
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [](Touch*touch,Event*event){return true;};

	listener->onTouchMoved = [&](Touch*touch,Event*event){
		Point pos2 = Director::getInstance()->convertToGL(touch->getLocationInView());
		/*if(pos2.x <= 0 || pos2.x >= visibleSize.width)
			return;*/
		Point pos1 = Director::getInstance()->convertToGL(touch->getPreviousLocationInView());
//		log("onTouchMoved");
		m_touchListener->setTagPosition(pos2 - pos1);
	};

	listener->onTouchEnded = [](Touch*touch,Event*event){};

	listener->onTouchCancelled = [](Touch*touch,Event*event){};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
}