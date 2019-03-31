#ifndef __Bullet_H__
#define __Bullet_H__
#include "Entity.h"
class Bullet:public Entity
{
	SDL_SYNTHESIZE(int,m_nHitPoint,HitPoint);//hp
	SDL_SYNTHESIZE(int,m_nDamage,Damage);//子弹伤害
	SDL_SYNTHESIZE(int,m_nSpeed,Speed);//子弹速度
	SDL_SYNTHESIZE(int,m_nAtkRange,AtkRange);//攻击范围
	SDL_SYNTHESIZE(std::string,m_normalImage,NormalImage);//正常图片
	SDL_SYNTHESIZE(std::string,m_deadImage,DeadImage);//死亡图片
	SDL_BOOL_SYNTHESIZE(m_bAvailable,Available);//是否可用
private:
	bool m_bDead;//是否死亡
public:
	Bullet();
	~Bullet();
	static Bullet*create(const std::string&name);
	bool init(const std::string&name);

	void hurt(int damage);
	void dead();
	FiniteTimeAction* onDeadAction();
	void setDead(bool dead);
	bool isDead()const;
};
#endif