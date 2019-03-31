#ifndef __Character_H__
#define __Character_H__

#include "Entity.h"
/*当前方向*/
enum class Direction
{
	None,/*无方向*/
	Left,/*向左*/
	Right,/*向右*/
	All,/*类似于None，为了Plant的适配,僵尸一般用不到*/
};
/*攻击类型*/
enum class AttackType
{
	Common,/*无效果,正常效果*/
	Boom,/*爆炸效果*/
	Ice,/*冰冻*/
	Swallow,/*吞噬效果*/
	Track,/*追踪效果*/
	Penetrate,/*穿透效果*/
	Magnet,/*磁力菇*/
	FireAndKillDeceleration,/*消冰火属性*/
	Deceleration,/*减速*/
	TrackAndDeceleration,/*追踪且减速*/
	TrackAndButter,/*追踪且黄油*/
};
/*角色类型*/
enum class CharacterType
{
	None,
	Plant,
	Zombie,
	Bullet,
};

class Character : public Entity
{
	SDL_SYNTHESIZE(int,m_nHitPoint,HitPoint);//当前血量
	SDL_SYNTHESIZE(int,m_nMaxHitPoint,MaxHitPoint);//最大血量
	SDL_BOOL_SYNTHESIZE(m_bDead,Dead);//标记当前是否死亡
	SDL_SYNTHESIZE(Direction,m_dir,Dir);//当前方向 移动方向即时攻击方向
	SDL_SYNTHESIZE(CharacterType,m_characterType,CharacterType);//角色类型
protected:
	static const int ANIMATION_TAG;
public:
	Character();
	~Character();
	/*受伤回调函数*/
	virtual void hurt(int baseDamage,AttackType attackType);
	/*将要死亡函数*/
	bool isDying()const;
public:
	/*获取精准的碰撞面积*/
	virtual Rect getCollisionBoundingBox()const;
protected:
	virtual void onHurt() = 0;
	/*获取当前所在行数*/
	virtual int getRow()const = 0;
};
#endif