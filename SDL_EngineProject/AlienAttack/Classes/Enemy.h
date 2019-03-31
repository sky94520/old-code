#ifndef __Enemy_H__
#define __Enemy_H__
#include "Entity.h"
#include "BulletLayer.h"

class FlyBehavior;
class ShootBehavior;

enum EnemyType
{
	kEnemyType_None,
	kEnemyType_Glider,//�����
	kEnemyType_ShotGlider,//�ᷢ���ӵ��Ļ����
	kEnemyType_Turret,//
	kEnemyType_RoofTurret,
	kEnemyType_Eskeletor,
	kEnemyType_Level1Boss
};
class Enemy:public Entity
{
	SDL_SYNTHESIZE(EnemyType,m_type,Type);//�л�����
	SDL_SYNTHESIZE(BulletType,m_bulletType,BulletType);//�ӵ�����
	SDL_SYNTHESIZE(float,m_speed,Speed);//�ٶ�
	SDL_SYNTHESIZE(int,m_worth,Worth);//��ֵ
	SDL_BOOL_SYNTHESIZE(m_bUpdate,Update);//�Ƿ�Ӧ�ø���
	SDL_SYNTHESIZE(float,m_elpased,Elpased);//����ֵ
	SDL_SYNTHESIZE(float,m_shootInterval,ShootInterval);//ÿ�����������
	SDL_SYNTHESIZE_RETAIN(Animate*,m_pDeadAction,DeadAction);//��������
private:
	FlyBehavior*m_pFlyBehavior;//������Ϊ
	ShootBehavior*m_pShootBehavior;//�����Ϊ
public:
	Enemy();
	~Enemy();
	CREATE_FUNC(Enemy);
	bool init();
	virtual void update(float dt);
	
	virtual void onDead();

	void setFlyBehavior(FlyBehavior*behavior);
	void setShootBehavior(ShootBehavior*behavior);
	void reset();
};
#endif