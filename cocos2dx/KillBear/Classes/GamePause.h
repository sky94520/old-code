#ifndef __GamePause_H__
#define __GamePause_H__
#include "cocos2d.h"
USING_NS_CC;
class GamePause : public Layer
{
public:
	GamePause();
	~GamePause();
	CREATE_FUNC(GamePause);
	virtual bool init();
};
#endif