#ifndef __BaseLayer_H__
#define __BaseLayer_H__
#include "cocos2d.h"
USING_NS_CC;
class BaseLayer:public Layer
{
public:
	CREATE_FUNC(BaseLayer);
	bool init();
	static Scene*createScene();
protected:
	virtual void menuBackCallback(Ref*);
};
#endif