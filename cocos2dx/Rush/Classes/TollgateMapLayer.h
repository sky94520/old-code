#ifndef __TollgateMapLayer_H__
#define __TollgateMapLayer_H__
#include "cocos2d.h"
#include "HeroManager.h"
#include "MonsterManager.h"
//±¤ÀÝ²ã´Î
#define HOME_LAYER_LVL 3
//Ó¢ÐÛ²ã´Î
#define HERO_LAYER_LVL 10
//¹ÖÎï²ã´Î
#define MONSTER_LAYER_LVL 15
//×Óµ¯²ã´Î
#define BULLET_LAYER_LVL 20
USING_NS_CC;
class TollgateMapLayer : public Layer
{
private:
	HeroManager*m_pHeroMgr;
	MonsterManager*m_pMonsterMgr;
	int m_nCurLevel;
public:
	TollgateMapLayer();
	~TollgateMapLayer();
	CREATE_FUNC(TollgateMapLayer);
	virtual bool init();
	static Scene*createScene();
	void loadConfig();
	//execute logic code
	void logic(float dt);
};
#endif