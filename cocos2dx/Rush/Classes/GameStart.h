#ifndef __GameStart_H__
#define __GameStart_H__
#include "cocos2d.h"
USING_NS_CC;
class GameStart : public Layer
{
public:
	GameStart();
	~GameStart();

	static Scene*createScene();
	CREATE_FUNC(GameStart);
	virtual bool init();
	//»Øµ÷º¯Êý
	void gameStart(Ref*pRef);
	void edit(Ref*pRef);
};
#endif