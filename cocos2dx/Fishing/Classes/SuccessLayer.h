#ifndef __SuccessLayer_H__
#define __SuccessLayer_H__
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocostudio;
using namespace ui;

class SuccessLayerDelegate
{
public:
	~SuccessLayerDelegate(){}
	virtual void gameRestart()=0;
	virtual void turnToLevelLayer()=0;
	virtual void nextLevel()=0;
};
class SuccessLayer:public Layer
{
private:
	SuccessLayerDelegate*m_pDelegate;
public:
	SuccessLayer();
	~SuccessLayer();
	CREATE_FUNC(SuccessLayer);
	bool init();

	void setDelegate(SuccessLayerDelegate*pDelegate);
private:
	void gameRestart(Ref*sender);
	void turnToLevelLayer(Ref*sender);
	void nextLevel(Ref*sender);
};
#endif