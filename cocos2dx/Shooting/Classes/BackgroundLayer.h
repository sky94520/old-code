#ifndef __BackgroundLayer_H__
#define __BackgroundLayer_H__
#include "cocos2d.h"
USING_NS_CC;
class BackgroundLayer:public Layer
{
private:
	Sprite*m_pBackground;
public:
	BackgroundLayer();
	~BackgroundLayer();
	bool init();
	CREATE_FUNC(BackgroundLayer);
};
#endif