#ifndef __PlaneAction_H__
#define __PlaneAction_H_
//

#include "cocos2d.h"
USING_NS_CC;

class PlaneAction : public cocos2d::Ref
{
public:
	static PlaneAction*getInstance();
	virtual bool init();

	ActionInterval*getActionByString(std::string str);
private:
	void split(int iFrame,std::string str,SpriteFrameCache*cache,float time,int loop);

	static PlaneAction*m_PlaneAction;
	Map<std::string,ActionInterval*> mActionMap;
};
#endif