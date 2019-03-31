#ifndef __Fish_H__
#define __Fish_H__
#include "Entity.h"
class Fish:public Entity
{
	SDL_SYNTHESIZE(int,m_nScore,Score);//这条鱼的分数
private:
	bool m_bAlive;//超出屏幕范围或被捕捉时为false
	float m_elpased;//在经过 n秒后出现
	
	float m_fSuccessRate;//被捕到的基础成功率
	unsigned int m_nID;
	unsigned int m_nRunFrame;
	unsigned int m_nDeadFrame;
	unsigned int m_nRareRate;//稀有率 ，表示一个场景最多能创建的数量
public:
	Fish();
	~Fish();
	CREATE_FUNC(Fish);
	static Fish*create(int id);
	bool init();
	bool init(int id);
public:
	//增加可重用性
	void reset();
	void show(float dt);//展示
	void catched();//被捕捉后调用
public:
	virtual void update(float dt);
	bool isAlive()const;
	float getSuccessRate()const;
	unsigned int getRareRate()const;
	int getID()const;
private:
	ActionInterval*lineRoute(const Point&from,const Point&to,float duration,bool direction);
};
#endif