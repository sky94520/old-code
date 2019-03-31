#ifndef __StateLayer_H__
#define __StateLayer_H__
#include "cocos2d.h"
#include "ui/CocosGUI.h"
using namespace cocos2d;
class StateLayer:public cocos2d::Layer
{
private:
	//hp
	ui::LoadingBar*m_pHpBar;
public:
	StateLayer();
	CREATE_FUNC(StateLayer);
	virtual bool init();

	virtual void update(float dt);
};
#endif