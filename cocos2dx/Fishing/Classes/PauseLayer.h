#ifndef __PauseLayer_H__
#define __PauseLayer_H__
#include "cocos2d.h"
USING_NS_CC;
class PauseLayerDelegate
{
public:
	virtual ~PauseLayerDelegate(){}
	virtual void gameResume()=0;
	virtual void turnToLevelLayer()=0;
};
class PauseLayer:public Layer
{
private:
	PauseLayerDelegate*m_pDelegate;
public:
	PauseLayer();
	~PauseLayer();
	CREATE_FUNC(PauseLayer);
	bool init();

	void gameResume(Ref*sender);
	void turnToLevelLevel(Ref*sender);
	void setDelegate(PauseLayerDelegate*pDelegate);

};
#endif