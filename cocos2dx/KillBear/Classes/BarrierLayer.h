#ifndef __BarrierLayer_H__
#define __BarrierLayer_H__
#include "cocos2d.h"
USING_NS_CC;
class BarrierLayer:public Layer
{
public:
	BarrierLayer();
	~BarrierLayer();
	CREATE_FUNC(BarrierLayer);
	virtual bool init() override;
};
#endif