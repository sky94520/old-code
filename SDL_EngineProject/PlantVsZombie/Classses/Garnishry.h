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
		Common,//��ͨ��Ʒ
		Iron,//������Ʒ
	};
	SDL_SYNTHESIZE(int,m_nMaxHitPoint,MaxHitPoint);//���Ѫ��ֵ
	SDL_SYNTHESIZE(int,m_nHitPoint,HitPoint);//��ǰѪ��
	SDL_SYNTHESIZE(Type,m_type,Type);//��Ʒ����
	SDL_SYNTHESIZE(string,m_garnishryName,GarnishryName);//��Ʒ����
	SDL_BOOL_SYNTHESIZE(m_bImmuneForIce,ImmuneForIce);//�Ƿ�Ա�������
private:
	HpBar*m_pHpBar;
public:
	Garnishry();
	~Garnishry();

	bool init(int hp);
	/**�����˺�ֵ
	*return ʣ�µ��˺�ֵ С��0������*/
	virtual int absorbDamage(int baseDamage,AttackType attackType);
	/*�Ƿ�Լ�������
	*bIsTrack �Ƿ���׷�����ӵ�*/
	virtual bool isImmuneForDeceleration(AttackType type)const;
	/*�Ƿ�Ի�������*/
	virtual bool isImmuneForButter()const;
protected:
	/*���ˣ�����ʣ����˺�ֵ*/
	int hurt(int damage);
};
//-------------------------·��Conehead----------------------------
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
//----------------Pole�Ÿ�----------------------------------
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