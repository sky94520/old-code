#ifndef __OperatorLayer_H__
#define __OperatorLayer_H__
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "Rocker.h"
USING_NS_CC;
using namespace extension;
class Hero;
class OperatorLayer : public Layer
{
private:
	Rocker*m_pRocker;
	ControlButton*m_pNormalAttackBtn;
public:
	//按钮是否被触摸
	bool m_bTouched;
public:
	OperatorLayer();
	~OperatorLayer();
	CREATE_FUNC(OperatorLayer);
	virtual bool init();
	//攻击按钮回调事件
	void touchDown(Ref* pSender,Control::EventType event);  
    void dragInside(Ref* pSender,Control::EventType event);  
    void dragOutside(Ref* pSender,Control::EventType event);  
    void dragEnter(Ref* pSender,Control::EventType event);  
    void dragExit(Ref* pSender,Control::EventType event);  
    void touchUpInside(Ref* pSender,Control::EventType event);  
    void touchUpOutside(Ref* pSender,Control::EventType event);  
    void touchCancel(Ref* pSender,Control::EventType event);  
    void valueChanged(Ref* pSender,Control::EventType event);  

	void normalAttackCallback(Ref* pSender,Control::EventType event);
};
#endif