#ifndef __Player_H__
#define __Player_H__
#include<string>
#include "SDL_Engine/SDL_Engine.h"
#include "Entity.h"
#include "Item.h"

using namespace std;
using namespace SDL;
//���ǵ�ǰ״̬
enum PlayerState
{
	kPlayerState_None,
	kPlayerState_Idle,//վ��״̬
	kPlayerState_Runnable,//��
	kPlayerState_Jumping,//��
	kPlayerState_Falling,//����
	kPlayerState_Dead,//����
	kPlayerState_Sit,//����״̬
};
//�����޵е�����
enum class InvulnerableType
{
	kNone,//����״̬
	kWithoutCollision,//��������ײ
	kCanHurtEnemy,//������ײ�����һ��˺�����
};
class Player:public Entity
{
	SDL_SYNTHESIZE(float,m_moveSpeed,MoveSpeed);//�ƶ��ٶ�
	SDL_BOOL_SYNTHESIZE(m_bCanJump,CanJump);//�Ƿ�����
	SDL_BOOL_SYNTHESIZE(m_bJumping,Jumping);//��ǰ�Ƿ�����������״̬
	SDL_SYNTHESIZE(PlayerState,m_curState,CurState);//��ǰ״̬
	SDL_SYNTHESIZE(int,m_curLevel,CurLevel);//���� 0 ��С 1 �� 2 ��ᷢ���ӵ�
	SDL_SYNTHESIZE(InvulnerableType,m_invulnerableType,InvulnerableType);//�����޵е�����
	SDL_SYNTHESIZE(int,m_bulletNum,BulletNum);
private:
	const static int ANIMATION_TAG;//���Ƕ�����tag
private:
	float m_invulnerableTime;//�������޵�ʱ��
public:
	Player();
	~Player();
	CREATE_FUNC(Player);
	bool init();
	//վ��
	void idle();
	void fall();//����
	void run(bool bRight = true);
	void jump();
	void sit();
	//����
	void ressurect(float invulnerableTime);
	void runIdleAnimation();//վ������
	void runRunnableAnimation();//�˶�����
	void runJumpingAnimation();//������
	void runSittingAnimation();//���¶���
	void runDeadAnimation();//��������
	//�����Ƿ��޵�
	bool isInvulnerable()const;
	//����
	void levelUp();
	//����
	void levelDown();
	//ʹ�������˺����˲����Լ���������
	void canHurtEnemyWithInvulnearability();
	//��ȡ�ɳ�����Ҫ�ĵ�������
	ItemType getGrowingItemType()const;
	//��ȡ���ǵ�ǰ���� ��ǰ�����Ƿ����� ��ͼƬ��Դ�й�
	bool isDirRight()const;
	//�ӵ������ص�����
	void bulletOver(EventCustom*);
	//��ǰ�����Ƿ���Է����ӵ�
	bool isCanShoot()const;

	virtual void onBindSprite();
	virtual bool onHurt(int damage);
	virtual void onDead();
	virtual	Rect getCollisionBoundingBox()const;

	virtual bool isInteractiveWithBlock()const;
	virtual bool isCanBrokeTile()const;
private:
	bool changeState(PlayerState nextState);
	//ʹmario�޵� �޵����ͣ��޵�ʱ��
	void makeSelfInvulnerable(InvulnerableType type,float invulnerableTime);
	//�޵к�ĺ����ص�
	//void endInvulnearableCallback(float elpased);
};
#endif