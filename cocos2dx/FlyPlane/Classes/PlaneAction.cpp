#include "PlaneAction.h"
PlaneAction*PlaneAction::m_PlaneAction = NULL;
PlaneAction*PlaneAction::getInstance()
{
	if(m_PlaneAction == NULL)
	{
		m_PlaneAction = new PlaneAction();
		if(m_PlaneAction && m_PlaneAction->init())
		{
			m_PlaneAction->autorelease();
			m_PlaneAction->retain();
		}
		else
		{
			CC_SAFE_DELETE(m_PlaneAction);
			m_PlaneAction = NULL;
		}
	}
	return m_PlaneAction;
}
bool PlaneAction::init()
{
	SpriteFrameCache*frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("Plane/Plane.plist","Plane/Plane.png");
	//加载主角平时帧
	split(2,std::string("player"),frameCache,0.1f,-1);
	//主角死亡帧
	split(4,std::string("player-dead"),frameCache,0.1f,1);
	//Small Plane dead
	split(5,std::string("Small Plane-dead"),frameCache,0.1f,1);
	//Middle Plane and dead
	split(5,std::string("Middle Plane-dead"),frameCache,0.1f,1);
	//子弹消失类
	split(2,std::string("bullet-dead"),frameCache,0.2f,1);
	//增加其他动画帧
	return true;
}
ActionInterval*PlaneAction::getActionByString(std::string str)
{
	if(mActionMap.find(str.c_str()) != mActionMap.end())
		return mActionMap.at(str.c_str());
	else
		return NULL;
}
void PlaneAction::split(int iFrame,std::string str,SpriteFrameCache*cache,float time,int loop)
{
	SpriteFrame*frame = NULL;
	Vector<SpriteFrame*> frameVec;

	for(int i = 1; i <= iFrame;i++)
	{
		frame = cache->getSpriteFrameByName(StringUtils::format("%s%i.png",str.c_str(),i));
		frameVec.pushBack(frame);
	}
	Animation*animation = Animation::createWithSpriteFrames(frameVec);

	animation->setLoops(loop);
	animation->setDelayPerUnit(time);
	animation->setRestoreOriginalFrame(true);

	Animate*act = Animate::create(animation);

	this->mActionMap.insert(str,act);
}