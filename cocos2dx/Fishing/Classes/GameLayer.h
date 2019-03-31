#ifndef __GameLayer_H__
#define __GameLayer_H__
#include "cocos2d.h"
#include "Fork.h"

USING_NS_CC;
class GameLayer:public Layer
{
private:
	Fork*m_pFork;
public:
	GameLayer();
	~GameLayer();
	CREATE_FUNC(GameLayer);
	bool init();

	Fork*getFork()const;
};
#endif