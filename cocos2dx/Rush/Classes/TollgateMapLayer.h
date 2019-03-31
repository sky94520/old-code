#ifndef __TollgateMapLayer_H__
#define __TollgateMapLayer_H__
#include "cocos2d.h"
#include "HeroManager.h"
#include "MonsterManager.h"
//���ݲ��
#define HOME_LAYER_LVL 3
//Ӣ�۲��
#define HERO_LAYER_LVL 10
//������
#define MONSTER_LAYER_LVL 15
//�ӵ����
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