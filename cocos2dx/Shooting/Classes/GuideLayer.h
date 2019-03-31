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
	//为什么要定义在类中，因为listener并不能addChild，所以如果用局部变量的话，并不能起到作用，反而会出错。定义在在类中，
	//listener会随着GuideLayer对象而加到addChild中
	EventListenerTouchOneByOne*listener;
};

#endif