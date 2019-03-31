#include "SunshineLayer.h"
#include "DynamicData.h"
SunshineLayer::SunshineLayer()
{
}
SunshineLayer::~SunshineLayer()
{
}
bool SunshineLayer::init()
{
	return true;
}
void SunshineLayer::update(float dt)
{
	for(int i=0;i<m_sunshines.size();i++)
	{
		auto sun = m_sunshines.at(i);
		//到达地面 并且没有被收集，则开始计算流逝值
		if(sun->isArriveLawn() && sun->isCollected() == false)
		{
			auto elapsed = dt + sun->getElapsed();
			sun->setElapsed(elapsed);
			if(elapsed >= 3.f)
			{
				m_sunshines.eraseObject(sun);
				sun->removeFromParent();
			}
		}
	}
}
void SunshineLayer::produceSunshine(const Point&startPos,SunshineType type,SunshineRoute route)
{
	auto sunshine = Sunshine::create(type);
	sunshine->setPosition(startPos);

	if(route == SunshineRoute::kSunshineRoute_jump)
	{
		//动作
		Size size = sunshine->getContentSize(); 
		int x = RANDOM(0,size.width);
		int y = RANDOM(0,size.height);
		//
		JumpBy*jump = JumpBy::create(0.8f,Point(x,y),-size.height,1);
		CallFunc*arrive = CallFunc::create([sunshine]()
		{
			sunshine->setArriveLawn(true);
		});
		sunshine->runAction(Sequence::createWithTwoActions(jump,arrive));
	}
	else if(route == SunshineRoute::kSunshineRoute_line)
	{
		auto visibleSize = Director::getInstance()->getVisibleSize();
		auto y = RANDOM(200,visibleSize.height);
		MoveBy*move = MoveBy::create(y/100,Point(0,y));
		CallFunc*arrive = CallFunc::create([sunshine]()
		{
			sunshine->setArriveLawn(true);
		});
		sunshine->runAction(Sequence::createWithTwoActions(move,arrive));
	}
	this->addChild(sunshine);
	m_sunshines.push_back(sunshine);
}
bool SunshineLayer::collectSunshine(const Point&pos)
{
	for(int i=0;i<m_sunshines.size();i++)
	{
		auto sun = m_sunshines.at(i);
		Rect rect = Rect(sun->getPosition(),sun->getContentSize());
		if(rect.containsPoint(pos))
		{
			//阳光被收集
			sun->setCollected(true);
			Point startPoint = rect.origin;
			float d = sqrt(pow(startPoint.x-300,2)+pow(startPoint.y,2));
			MoveTo*move = MoveTo::create(d/400,Point(300,0));
			CallFunc*addSunNum = CallFunc::create([&,sun]()
			{
				DynamicData::getInstance()->alertSunNum(sun->getSunshineType());
				m_sunshines.eraseObject(sun);
				sun->removeFromParent();
			});
			sun->stopAllActions();
			sun->runAction(Sequence::createWithTwoActions(move,addSunNum));
			return true;
		}
	}
	return false;
}