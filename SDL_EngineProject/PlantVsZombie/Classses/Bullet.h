#ifndef __Bullet_H__
#define __Bullet_H__
#include <vector>
#include <functional>
#include "SDL_Engine/SDL_Engine.h"
#include "Character.h"

using namespace std;
using namespace SDL;

enum class BulletType
{
	Common,
	ShooterPeaBullet,
};
class ZombieBase;

class Bullet : public Character
{
public:
	SDL_SYNTHESIZE(int,m_nDamage,Damage);//��ǰ�˺�
	SDL_SYNTHESIZE(AttackType,m_attackType,AttackType);//��������
	SDL_SYNTHESIZE(float,m_duration,Duration);//debuff����ʱ��
	SDL_SYNTHESIZE(BulletType,m_bulletType,BulletType);//�ӵ�����
	SDL_BOOL_SYNTHESIZE(m_bCanTransform,CanTransform);//�Ƿ����ת��
	SDL_SYNTHESIZE(function<void ()>,m_stopRunningCallback,StopRunningCallback);//ֹͣ���лص�����
	SDL_SYNTHESIZE(function<void ()>,m_deadCallback,DeadCallback);//�����ص�����
protected:
	ZombieBase*m_pAimZombie;
	//�����Ѿ��������Ľ�ʬ�б�
	vector<ZombieBase*> m_attackedZombieList;
	int m_nRow;
public:
	Bullet();
	~Bullet();
	//����Ŀ�Ľ�ʬ
	void setAimZombie(ZombieBase*zombie);
	ZombieBase*getAimZombie();
	//��ӹ��ﵽ�ѹ����б���
	void addAttackedZombie(ZombieBase*zombie);
	//�Ƿ��Ѿ��Ѿ��������ý�ʬ��
	bool isHasAttacked(ZombieBase*zombie);
	void setRow(int row);
	//���˺���
	void hurt();
	virtual int getRow()const;
	//��ײ���������
	virtual void contactEnd();
	//�Ƿ���׷�����ӵ�
	static bool isTrackBullet(AttackType attackType);
	//�Ƿ��Ǽ����ӵ�
	static bool isDecelerationBullet(AttackType attackType);
	//�Ƿ��ǻ����ӵ�
	static bool isButterBullet(AttackType attackType);
protected:
	virtual void onHurt();
	void rotateInnerSprite();
	void dieAfterRunningAnimation(const string &animationName);
private:
	void hurt(int damage,AttackType attackType);
};
//-----------------------�㶹�ӵ�PeaBullet------------------------------
class PeaBullet : public Bullet
{
public:
	CREATE_FUNC(PeaBullet);
	bool init();

	virtual void onHurt();
};
//---------------------��ըBoom-------------------------
class Boom : public Bullet
{
	SDL_SYNTHESIZE(Rect,m_collisionRect,CollisionRect);
public:
	Boom();
	~Boom();
	CREATE_FUNC(Boom);
	bool init();

	virtual void contactEnd();
	virtual Rect getCollisionBoundingBox()const;
};
//------------------------CabbageBullet----------------------
class CabbageBullet : public Bullet
{
public:
	CREATE_FUNC(CabbageBullet);
	bool init();

	virtual void onHurt();
};
//------------------SnowPeaBullet----------------------------
class SnowPeaBullet : public Bullet
{
public:
	CREATE_FUNC(SnowPeaBullet);
	bool init();
	virtual void onHurt();
};
//-------------------FirePeaBullet----------------------------
class FirePeaBullet : public Bullet
{
private:
	bool m_bFirst;
	int m_nTime;
public:
	FirePeaBullet();
	CREATE_FUNC(FirePeaBullet);
	bool init();
	virtual void onHurt();
	virtual void contactEnd();
	virtual Rect getCollisionBoundingBox()const;
};
//-------------------FumeShroomBullet------------------------
class FumeShroomBullet : public Bullet
{
	SDL_SYNTHESIZE(float,m_fAtkScope,AtkScope);//������Χ
public:
	FumeShroomBullet();
	CREATE_FUNC(FumeShroomBullet);
	bool init();

	virtual Rect getCollisionBoundingBox()const;
	virtual void contactEnd();
};
//-----------------ShroomBullet-----------------------------
class ShroomBullet : public Bullet
{
public:
	CREATE_FUNC(ShroomBullet);
	bool init();

	virtual void onHurt();
	virtual Rect getCollisionBoundingBox()const;
};
//------------------------CornBullet----------------------
class CornpultBullet : public Bullet
{
public:
	static CornpultBullet*create(bool isButter);
	bool init(bool isButter);

	virtual void onHurt();
};
#endif