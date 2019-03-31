#ifndef __Zombie_H__
#define __Zombie_H__
#include "Entity.h"
typedef enum ZombieStatus
{
	kZombieStatus_None,//��״̬
	kZombieStatus_Idle,//վ��״̬
	kZombieStatus_Walk,//����״̬
	kZombieStatus_Attack,//����״̬
	kZombieStatus_DeadAttack,//��������״̬
	kZombieStatus_DeadWalk,//��������״̬
	kZombieStatus_DeadBomb,//ը��״̬
	kZombieStatus_EntireDead//��ȫ����״̬
}ZombieStatus;
class Plant;
class HpBar;
class Zombie:public Entity
{
	SDL_SYNTHESIZE(int,m_nHitPoint,HitPoint);//Ѫ��
	SDL_SYNTHESIZE(int,m_nDefense,Defense);//����
	SDL_SYNTHESIZE(float,m_fSpeed,Speed);//�ƶ��ٶ�
	SDL_SYNTHESIZE(ZombieStatus,m_status,ZombieStatus);//��ʬ��ǰ״̬
	SDL_SYNTHESIZE(float,m_fSkillTime,SkillTime);//����ʱ����
	SDL_SYNTHESIZE(float,m_showTime,ShowTime);//����ʱ��
	SDL_SYNTHESIZE(float,m_elapsed,Elapsed);//��ǰ����ʱ��
	SDL_SYNTHESIZE(int,m_nRoute,Route);//·��
private:
	HpBar*m_pHpBar;
	Sprite*m_pHead;//��ʬͷ
public:
	Zombie();
	~Zombie();
	CREATE_FUNC(Zombie);
	bool init();

	void hurt(int damage);
	void dead();
	bool changeState(ZombieStatus status);
	//�ı�״̬������������Ӧ����
	bool runIdleAction();
	bool runWalkAction();
	bool runAttackAction();
	bool runLostHeadAction();//ʧȥͷ�˶�����
	bool runLostAttackAction();//������������
	bool runEntireDeadAction();
	bool runDeadBombAction();//��ը��

	virtual void onHurt();//����ʱ����
	virtual void onDead();//����ʱ����

	virtual void attack(Plant*plant,float dt);

	virtual FiniteTimeAction*onIdleAction();
	virtual FiniteTimeAction*onWalkAction();
	virtual FiniteTimeAction*onAttackAction();
	virtual FiniteTimeAction*onLostHeadAction();
	virtual FiniteTimeAction*onLostAttackAction();
	virtual FiniteTimeAction*onEntireDeadAction();
	virtual FiniteTimeAction*onHeadAction();
	virtual FiniteTimeAction*onDeadBombAction();
};
#endif