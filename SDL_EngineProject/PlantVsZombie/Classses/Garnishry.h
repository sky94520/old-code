#ifndef __Garnishry_H__
#define __Garnishry_H__
#include "SDL_Engine/SDL_Engine.h"
#include "Entity.h"
#include "Bullet.h"

using namespace SDL;
class HpBar;

class Garnishry : public Entity
{
public:
	enum class Type
	{
		Common,//普通饰品
		Iron,//铁质饰品
	};
	SDL_SYNTHESIZE(int,m_nMaxHitPoint,MaxHitPoint);//最大血量值
	SDL_SYNTHESIZE(int,m_nHitPoint,HitPoint);//当前血量
	SDL_SYNTHESIZE(Type,m_type,Type);//饰品类型
	SDL_SYNTHESIZE(string,m_garnishryName,GarnishryName);//饰品名称
	SDL_BOOL_SYNTHESIZE(m_bImmuneForIce,ImmuneForIce);//是否对冰块免疫
private:
	HpBar*m_pHpBar;
public:
	Garnishry();
	~Garnishry();

	bool init(int hp);
	/**吸收伤害值
	*return 剩下的伤害值 小于0则不受伤*/
	virtual int absorbDamage(int baseDamage,AttackType attackType);
	/*是否对减速免疫
	*bIsTrack 是否是追踪型子弹*/
	virtual bool isImmuneForDeceleration(AttackType type)const;
	/*是否对黄油免疫*/
	virtual bool isImmuneForButter()const;
protected:
	/*受伤，返回剩余的伤害值*/
	int hurt(int damage);
};
//-------------------------路障Conehead----------------------------
class Conehead : public Garnishry
{
public:
	Conehead();
	~Conehead();
	static Conehead*create(int hp);
	bool init(int hp);
	virtual int absorbDamage(int baseDamage,AttackType attackType);
};
//-------------------------Paper-------------------------------
class Paper : public Garnishry
{
public:
	static Paper*create(int hp);
	bool init(int hp);

	virtual int absorbDamage(int baseDamage,AttackType attackType);
	virtual bool isImmuneForDeceleration(AttackType type)const;
};
//----------------Pole撑杆----------------------------------
class Pole : public Garnishry
{
public:
	CREATE_FUNC(Pole);
	bool init();
	virtual int absorbDamage(int baseDamage,AttackType attackType);
};
//-------------------------Bucket------------------------------
class Bucket : public Garnishry
{
public:
	static Bucket*create(int hp);
	bool init(int hp);
	virtual int absorbDamage(int baseDamage,AttackType attackType);
};
//-------------------------Helemt----------------------------
class Helmet : public Garnishry
{
public:
	static Helmet*create(int hp);
	bool init(int hp);
	virtual int absorbDamage(int baseDamage,AttackType attackType);
};
//-------------------------ScreenDoor----------------------------
class ScreenDoor : public Garnishry
{
public:
	static ScreenDoor*create(int hp);
	bool init(int hp);
	virtual int absorbDamage(int baseDamage,AttackType attackType);
	virtual bool isImmuneForDeceleration(AttackType type)const;
};
#endif