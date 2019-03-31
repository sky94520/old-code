#ifndef __DefeatLayer_H__
#define __DefeatLayer_H__
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocostudio;
using namespace ui;
/*Ê§°Ü²ã*/
class DefeatLayerDelegate
{
public:
	virtual ~DefeatLayerDelegate(){}
	virtual void gameRestart()=0;
	virtual void turnToLevelLayer()=0;
};
class DefeatLayer:public Layer
{
private:
	DefeatLayerDelegate*m_pDelegate;
public:
	DefeatLayer();
	~DefeatLayer();
	CREATE_FUNC(DefeatLayer);
	bool init();
	void setDelegate(DefeatLayerDelegate*pDelegate);
private:
	void gameRestart(Ref*sender);
	void turnToLevelLayer(Ref*sender);
};
#endif