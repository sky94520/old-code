#ifndef __GoldTimer_H__
#define __GoldTimer_H__
/*金币计时器*/
#include "Entity.h"
class GoldTimer:public Node
{
private:
	//每次要增长的金币数目
	int m_nGold;
	//每过多少秒进行增加金币
	int m_nSecond;
	float m_elpased;//当前流逝时间
	//显示时间的Label
	LabelAtlas*m_pLabel;
public:
	GoldTimer();
	~GoldTimer();
	CREATE_FUNC(GoldTimer);
	bool init();
	virtual void update(float dt);
};
#endif