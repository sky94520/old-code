#ifndef __Entity_H__
#define __Entity_H__
#include<vector>
#include "SDL_Engine/SDL_Engine.h"

using namespace SDL;
using namespace std;

class Entity:public Node
{
	SDL_BOOL_SYNTHESIZE(m_bDead,Dead);//是否死亡
	SDL_SYNTHESIZE(int,m_nCurHp,CurHp);//当前hp
	SDL_SYNTHESIZE(int,m_nMaxHp,MaxHp);//最大hp
	SDL_SYNTHESIZE(Point,m_heading,Heading);//当前朝向，并带有速度大小
protected:
	Sprite*m_pSprite;
public:
	Entity();
	~Entity();
	void bindSprite(Sprite*sprite);
	Sprite*getSprite()const;
	//创建动画[begin,end]暂时这样，使用AnimationCache还是createAnimate
	static Animate*createAnimate(std::string format,int begin,int end,float delayPerUnit,unsigned int loops=-1);
public:
	void hurt(int damage);
	//是否将会死亡
	bool isDying()const;
	//hook
	virtual void onBindSprite();
	virtual void onHurt(int damage);
	virtual void onDead();
};
#endif