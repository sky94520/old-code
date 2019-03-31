#ifndef __Entity_H__
#define __Entity_H__
#include<vector>
#include "SDL_Engine/SDL_Engine.h"

using namespace SDL;
using namespace std;

class Entity:public Node
{
	SDL_BOOL_SYNTHESIZE(m_bDead,Dead);//�Ƿ�����
	SDL_SYNTHESIZE(int,m_nCurHp,CurHp);//��ǰhp
	SDL_SYNTHESIZE(int,m_nMaxHp,MaxHp);//���hp
	SDL_SYNTHESIZE(Point,m_heading,Heading);//��ǰ���򣬲������ٶȴ�С
protected:
	Sprite*m_pSprite;
public:
	Entity();
	~Entity();
	void bindSprite(Sprite*sprite);
	Sprite*getSprite()const;
	//��������[begin,end]��ʱ������ʹ��AnimationCache����createAnimate
	static Animate*createAnimate(std::string format,int begin,int end,float delayPerUnit,unsigned int loops=-1);
public:
	void hurt(int damage);
	//�Ƿ񽫻�����
	bool isDying()const;
	//hook
	virtual void onBindSprite();
	virtual void onHurt(int damage);
	virtual void onDead();
};
#endif