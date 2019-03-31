#ifndef __RotateWithAction_H__
#define __RotateWithAction_H__
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;
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
};
#endif