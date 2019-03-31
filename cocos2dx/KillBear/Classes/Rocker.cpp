#include "Rocker.h"
#include "Hero.h"
#include "Global.h"
Rocker::Rocker()
{
	Global::getInstance()->m_pRocker = this;
}
bool Rocker::init()
{
	m_pRocker = NULL;
	m_pRockerBG = NULL;
	m_bIsActive = false;
	m_pTouchListener = NULL;
	m_bCanMove = false;
	//Æô¶¯update
	this->scheduleUpdate();
	return true;
}
Rocker*Rocker::createRocker(std::string rockerFileName,std::string rockerBGFileName,const Point*position)
{
	Rocker*rocker = Rocker::create();
	if(rocker&&rocker->initRocker(rockerFileName,rockerBGFileName,position))
		return rocker;
	else
		CC_SAFE_DELETE(rocker);
	return nullptr;
}
bool Rocker::initRocker(std::string rockerFileName,std::string rockerBGFileName,const Point*position)
{
	m_pRocker = Sprite::create(rockerFileName);
	m_pRockerBG = Sprite::create(rockerBGFileName);
	m_pRocker->setVisible(false);
	m_pRockerBG->setVisible(false);
	this->addChild(m_pRocker,1);
	this->addChild(m_pRockerBG,0);
	//·ÅÖÃµ½ºÏÊÊÎ»ÖÃ
	Size bgSize = m_pRockerBG->getContentSize();

	m_pRockerBG->setPosition(Point(bgSize.width/2+position->x,bgSize.height/2+position->y));
	m_pRocker->setPosition(Point(bgSize.width/2+position->x,bgSize.height/2+position->y));
	//¸³Öµ
	m_pTouchListener = EventListenerTouchOneByOne::create();
	m_pTouchListener->onTouchBegan = CC_CALLBACK_2(Rocker::onTouchBegan,this);
	m_pTouchListener->onTouchMoved = CC_CALLBACK_2(Rocker::onTouchMoved,this);
	m_pTouchListener->onTouchEnded = CC_CALLBACK_2(Rocker::onTouchEnded,this);
	return true;
}
void Rocker::start()
{
	if(!m_bIsActive)
	{
		m_bIsActive = true;
		m_pRocker->setVisible(true);
		m_pRockerBG->setVisible(true);
		//Ìí¼Ó¼àÌýÆ÷
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_pTouchListener,this);
	}
}
void Rocker::stop()
{
	if(m_bIsActive)
	{
		m_bIsActive = false;
		m_pRocker->setVisible(false);
		m_pRockerBG->setVisible(false);
		//delete¼àÌýÆ÷
		_eventDispatcher->removeEventListener(m_pTouchListener);

	}
}
Point Rocker::getDirection()
{
	//»ñÈ¡¾«Áém_pRockerµÄ×ø±ê
	Point point1 = m_pRocker->getPosition();
	Point point2 = m_pRockerBG->getPosition();
	float x = point1.x - point2.x;
	float y = point1.y - point2.y;
	//°ë¾¶Îª±³¾°µÄÒ»°ë
	float radius = m_pRockerBG->getBoundingBox().size.width/2;
	return Point(x/radius,y/radius);
}
bool Rocker::onTouchBegan(Touch*touch,Event*e)
{
	//ÅÐ¶ÏÊÇ·ñÔÚ±³¾°·¶Î§ÄÚ
	Point touchPoint = touch->getLocation();
	if(m_pRockerBG->getBoundingBox().containsPoint(touchPoint))
	{
		m_pRocker->setPosition(touchPoint);
		m_bCanMove = true;
		Global::getInstance()->m_pHero->onMove(getDirection());
	}
	return true;
}
void Rocker::onTouchMoved(Touch*touch,Event*e)
{
	if(!m_bCanMove)
			return;
	//ÅÐ¶ÏÊÇ·ñÔÚ±³¾°·¶Î§ÄÚ
	Point touchPoint = touch->getLocation();
	Point bgPoint = m_pRockerBG->getPosition();
	if(!m_pRockerBG->getBoundingBox().containsPoint(touchPoint))
	{
		float radius = m_pRockerBG->getContentSize().width/2;
		float d = sqrt(pow(touchPoint.x - bgPoint.x,2)+pow(touchPoint.y - bgPoint.y,2));
		float x = radius/d*(touchPoint.x - bgPoint.x) + bgPoint.x;
		float y = radius/d*(touchPoint.y - bgPoint.y) + bgPoint.y;
		m_pRocker->setPosition(Point(x,y));
	}
	else
		m_pRocker->setPosition(touchPoint);
	//
	Global::getInstance()->m_pHero->onMove(getDirection());
}
void Rocker::onTouchEnded(Touch*touch,Event*e)
{
	Point point = m_pRockerBG->getPosition();
	m_pRocker->setPosition(point);
	m_bCanMove = false;
	Global::getInstance()->m_pHero->onStop();
}