#ifndef __Enemy_H__
#define __Enemy_H__
#include "BehaviorEntity.h"
#include "SDL_Engine/SDL_Engine.h"
#include "EnemyLayer.h"

using namespace SDL;

class MoveBehavior;
class Player;

enum class EnemyHurtType
{
	None,//δ�ܵ��˺�
	Bullet,//���ӵ����˺�
	Stamp,//��mario�ȵ�
	Star,//�ܵ����ǵ��˺�
	Enemy,//�ܵ����˵��˺�
};
/*һ�е��˵Ļ���*/
class Enemy:public BehaviorEntity
{
	SDL_BOOL_SYNTHESIZE(m_bBulletImmune,BulletImmune);//�Ƿ���ӵ�����
	SDL_BOOL_SYNTHESIZE(m_bStampImmune,StampImmune);//�Ƿ�Բ����ߣ�������˺�mario
	SDL_BOOL_SYNTHESIZE(m_bStarImmune,StarImmune);//�Ƿ����������
	SDL_BOOL_SYNTHESIZE(m_bEnemyImmune,EnemyImmune);//�Ƿ�Ե�����ɵ��˺�����
	SDL_BOOL_SYNTHESIZE(m_bCanHurtEnemy,CanHurtEnemy);//�Ƿ���˺�����
	SDL_BOOL_SYNTHESIZE(m_bCollidedWithEnemyFlag,CollidedWithEnemyFlag);//��ײ��ǣ������ظ���ײ
	SDL_BOOL_SYNTHESIZE(m_bCollidedWithPlayerFlag,CollidedWithPlayerFlag);
protected:
	static const int ENEMY_ANIMATION_TAG;//����ֻ������һ��
public:
	Enemy();
	~Enemy();
	//����Ѫ��
	void hurt(Entity*entity,EnemyHurtType hurtType);
	//�����ڲ�״̬ ����ֵ Ϊtrue���Խ��п�Ѫ�ж�
	virtual bool onHurt(Entity*entity,EnemyHurtType hurtType);
	//�ı�x�᷽�򣬽����Ƿ���
	virtual void changeDirectionX();

	virtual void onDead(EnemyHurtType hurtType)=0;
	virtual void runRunnableAnimation()=0;//�������߶���
	virtual bool tileCollidedX(bool bRight)=0;
	virtual bool tileCollidedY(bool bDown)=0;
};
//-----------------------------����Ģ��-----------------------------------
class TriMushroom:public Enemy
{
public:
	TriMushroom();
	~TriMushroom();
	CREATE_FUNC(TriMushroom);
	bool init();

	virtual void onDead(EnemyHurtType hurtType);

	virtual void runRunnableAnimation();
	virtual Rect getCollisionBoundingBox()const;

	virtual bool tileCollidedX(bool bRight);
	virtual bool tileCollidedY(bool bDown);
};
//---------------------------- Tortoise----------------------------
class Tortoise:public Enemy
{
	SDL_SYNTHESIZE(Point,m_oldVelocity,OldVelocity);//�������ڹ�һ��ʼ���ٶ�
public:
	enum TortoiseStateType
	{
		kTortoiseState_Run,//�˶�״̬
		kTortoiseState_SinkHead,//��ͷ״̬
		kTortoiseState_RunAndSinkHead,//��ͷ���������˶�
	};
private:
	float m_ressurectTime;//����ʱ��
	const static string m_ressurectScheduleStr;//�����ʱ������
	TortoiseStateType m_stateType;//״̬����
	bool m_bLeft;//��ǰ�Ƿ���������
public:
	Tortoise();
	~Tortoise();
	CREATE_FUNC(Tortoise);
	bool init();

	virtual bool onHurt(Entity*entity,EnemyHurtType hurtType);
	virtual void onDead(EnemyHurtType hurtType);

	virtual bool isInteractiveWithBlock()const;
	virtual bool isCanBrokeTile()const;

	virtual void runRunnableAnimation();
	virtual Rect getCollisionBoundingBox()const;

	virtual void changeDirectionX();
	virtual bool tileCollidedX(bool bRight);
	virtual bool tileCollidedY(bool bDown);
private:
	void ressurectPeriodOne();//�����׶�1
	void ressurectPeriodTwo(float dt);//�����׶�2 ��ʱ
	void ressurectPeriodThree(float dt);//�����׶�3
};
//--------------------------------WingEnemyDecorator���װ����-----------------
class WingEnemyDecorator:public Enemy
{
private:
	Enemy*m_pInnerEnemy;
	bool m_bWingDead;//����Ƿ�����
	float const MAX_JUMP_HEIGHT;//������Ծ����߾���
	float m_curJumpHeight;
	//��ǰ�˶������Ƿ�����
	bool m_bLeft;
public:
	WingEnemyDecorator();
	~WingEnemyDecorator();
	static WingEnemyDecorator*create(Enemy*enemy);
	bool init(Enemy*enemy);

	virtual bool onHurt(Entity*entity,EnemyHurtType hurtType);
	virtual void onDead(EnemyHurtType hurtType);
	virtual void changeDirectionX();
	virtual bool isInteractiveWithBlock()const;
	virtual bool isCanBrokeTile()const;

	virtual void runRunnableAnimation();
	virtual Rect getCollisionBoundingBox()const;
	virtual void performMove(float dt);

	virtual bool tileCollidedX(bool bRight);
	virtual bool tileCollidedY(bool bDown);
};
//-----------------------------Chomper---------------------------------
class Chomper:public Enemy
{
	SDL_SYNTHESIZE(float,m_maxJumpHeight,MaxJumpHeight);
	SDL_SYNTHESIZE(Rect,m_shapeRect,ShapeRect);
private:
	float m_curJumpHeight;
	float m_delayTime;//����ߵ��ͣ��ʱ��
	float m_elpased;//����ʱ��
	EnemyDelegate*m_pDelegate;
public:
	Chomper();
	~Chomper();
	CREATE_FUNC(Chomper);
	bool init();

	virtual bool onHurt(Entity*entity,EnemyHurtType hurtType);
	virtual void onDead(EnemyHurtType hurtType);

	virtual void runRunnableAnimation();//�������߶���
	virtual void performMove(float dt);

	virtual bool tileCollidedX(bool bRight){return false;}
	virtual bool tileCollidedY(bool bDown){return false;}

	void setDelegate(EnemyDelegate*pDelegate);
};
#endif