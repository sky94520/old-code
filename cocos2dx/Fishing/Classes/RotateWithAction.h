#ifndef __RotateWithAction_H__
#define __RotateWithAction_H__
#include "cocos2d.h"
USING_NS_CC;
class Entity;
class RotateWithAction:public ActionInterval
{
private:
	ActionInterval*m_pInnerAction;
public:
	RotateWithAction();
	~RotateWithAction();
	static RotateWithAction*create(ActionInterval*action);
	bool init(ActionInterval*action);

	virtual void startWithTarget(Node*target);
	virtual bool isDone()const;
	virtual void update(float time);
	virtual void stop();
	//virtual RotateWithAction*clone()const;
};
#endif