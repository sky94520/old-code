#ifndef __Bullet_H__
#define __Bullet_H__
#include "Entity.h"
/*子弹类型*/
enum BulletType
{
	kBulletType_None,
	kBulletType_Small,
	kBulletType_Middle,
	kBulletType_Big,
};
class Bullet:public Entity
{
	SDL_SYNTHESIZE(int,m_damage,Damage);//攻击力
	SDL_SYNTHESIZE(float,m_speed,Speed);//速度
	SDL_SYNTHESIZE_RETAIN(Animate*,m_pDeadAction,DeadAction);
	SDL_SYNTHESIZE(BulletType,m_type,BulletType);
public:
	Bullet();
	~Bullet();
	CREATE_FUNC(Bullet);

	static Bullet*create(Sprite*sprite);
	bool init();
	bool init(Sprite*sprite);
	void reset();

	virtual void onDead();
};
#endif