#ifndef __GameScene_H__
#define __GsmeScene_H__
#include "cocos2d.h"
#include "Hero.h"
class GameScene : public cocos2d::Layer
{
private:
	Hero*m_pHero;
public:
	GameScene();
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameScene);
	virtual void update(float dt);
};

#endif
