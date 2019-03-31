#ifndef __Bird_H__
#define __Bird_H__
#include "Entity.h"

class Bird:public Entity
{
	SDL_BOOL_SYNTHESIZE(m_bFlying,Flying);//当前小鸟是否正在飞行
private:
	int m_id;//决定当前是哪种小鸟，目前仅是贴图不同
	float m_elapsed;//小鸟下降的时间
	bool m_bDead;//小鸟是否死亡
public:
	Bird();
	~Bird();
	static Bird*create(int id);
	bool init(int id);
	void fly();//鸟儿升起
	void down(float dt);//小鸟下降
	void dead();//小鸟死亡
};
#endif