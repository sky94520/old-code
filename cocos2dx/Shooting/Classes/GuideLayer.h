#ifndef __GuideLayer_H__
#define __GuideLayer_H__
#include "cocos2d.h"
USING_NS_CC;

class GuideLayer :public Node
{
public:
	CREATE_FUNC(GuideLayer);
	virtual bool init();
	GuideLayer();
	~GuideLayer();
private:
	LayerColor*area1;
	LayerColor*area2;
	LayerColor*area3;
	LayerColor*area4;
	Color4B defaultColor;

	bool onTouchBegan(Touch*touch,Event*event);
	//ΪʲôҪ���������У���Ϊlistener������addChild����������þֲ������Ļ��������������ã���������������������У�
	//listener������GuideLayer������ӵ�addChild��
	EventListenerTouchOneByOne*listener;
};

#endif