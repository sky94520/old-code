#include "Monster.h"
#include "CsvUtil.h"

Monster::Monster()
{
	m_isAlive = false;
}
Monster::~Monster()
{
}
bool Monster::init()
{
	return true;
}
void Monster::reset()
{
	if(m_sprite ==NULL)
		return ;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Size planeSize = m_sprite->getContentSize();
	int range = visibleSize.width - planeSize.width;
	setPosition(rand()%range + planeSize.width/2,visibleSize.height + visibleSize.height * CCRANDOM_0_1());
}
void Monster::hide()
{
	if(m_sprite == NULL)
		return;
	//
	setVisible(false);
	reset();
	m_isAlive = false;
}
void Monster::show()
{
	if(m_sprite == NULL)
		return;
	setVisible(true);
	m_isAlive = true;
}
bool Monster::isAlive()
{
	return m_isAlive;
}

int Monster::getSpeed()
{
	if(m_sprite != NULL)
		return this->m_speed;
}
void Monster::setSpeed(int iSpeed)
{
	this->m_speed = iSpeed;
}
void Monster::run(Action*act)
{
	if(this->m_sprite != NULL)
	{
		CallFunc*callFunc = CallFunc::create([&](){
		
			this->hide();
			//ÉèÖÃhp
			if(this->m_id == std::string("Small Plane"))
				this->setHitPoints(CsvUtil::getInstance()->getValue(2,2,"Plane.csv").asInt());
			else if(this->m_id == std::string("Middle Plane"))
				this->setHitPoints(CsvUtil::getInstance()->getValue(5,1,"Plane.csv").asInt());
		
		});
		
		Action*allActions = Sequence::create((ActionInterval*)act,callFunc,NULL);

		this->stopAllActions();
		m_sprite->runAction(allActions->clone()); 
	}
}