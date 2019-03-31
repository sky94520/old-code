#ifndef __MenuLayer_H__
#define __MenuLayer_H__
#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace cocos2d::ui;
class MenuLayerDelegate
{
public:
	virtual ~MenuLayerDelegate(){}
	virtual void gameResume()=0;
	virtual void gameRestart()=0;
	virtual void gameEnd()=0;
};
class MenuLayer:public Layer
{
private:
	Label*m_pScoreLabel;
	MenuItem*m_pContinueBtn;
	MenuLayerDelegate*m_pDelegate;
public:
	MenuLayer();
	~MenuLayer();
	CREATE_FUNC(MenuLayer);
	bool init();

	void setDelegate(MenuLayerDelegate*pDelegate);
	void gameOver();
private:
	void gameResume(Ref*);
	void gameRestart(Ref*);
	void gameEnd(Ref*);
};
#endif