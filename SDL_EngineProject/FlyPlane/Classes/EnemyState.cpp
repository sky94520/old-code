#include "EnemyState.h"
#include "Plane.h"
#include "EnemyStateFSM.h"
ChaseState::ChaseState(EnemyStateFSM*fsm)
	:EnemyState(fsm)
{
}
void ChaseState::chase(Plane*enemy,Plane*player)
{
	m_pFSM->chasePlayer(enemy,player);
}
void ChaseState::flee(Plane*enemy,Plane*player)
{
	//chase -> flee
	/*m_pFSM->setState(m_pFSM->getFleeState());
	m_pFSM->flee(enemy,player);*/
}
void ChaseState::shoot(Plane*enemy,Plane*player)
{
	//����ɹ�,��ת״̬
	if(m_pFSM->shootPlayer(enemy,player))
		m_pFSM->setState(m_pFSM->getShootState());
	else//���ʧ�ܣ�׷��
		m_pFSM->chasePlayer(enemy,player);
}
//-----------------------------FleeState----------------------------------
FleeState::FleeState(EnemyStateFSM*fsm)
	:EnemyState(fsm)
{
}
void FleeState::chase(Plane*enemy,Plane*player)
{
	m_pFSM->setState(m_pFSM->getChaseState());
	m_pFSM->chase(enemy,player);
}
void FleeState::flee(Plane*enemy,Plane*player)
{
	//���ܣ����ǰѷɻ��ĽǶȵ�����player���ڵ�λ��
	Point delta = player->getPosition() - enemy->getPosition();
	float degree = atan2(delta.y,delta.x);
	//ת��Ϊ�Ƕ�
	float angle = SDL_DEGREE_TO_ANGLE(degree);
	if(angle > 0)
		angle = 180 - angle;
	else if(angle < 0)
		angle = abs(angle) - 180;

	RotateTo*rotate = RotateTo::create(abs(angle/90.f),angle);
	//������ת����
	enemy->getSprite()->stopAllActions();
	enemy->getSprite()->runAction(rotate);
}
void FleeState::shoot(Plane*enemy,Plane*player)
{
	//����״̬�²��᳢�����
}
//-----------------------------ShootState----------------------------------
ShootState::ShootState(EnemyStateFSM*fsm)
	:EnemyState(fsm)
{
}
void ShootState::chase(Plane*enemy,Plane*player)
{
	m_pFSM->chasePlayer(enemy,player);
	m_pFSM->setState(m_pFSM->getChaseState());
}
void ShootState::flee(Plane*enemy,Plane*player)
{
	/*m_pFSM->setState(m_pFSM->getFleeState());
	m_pFSM->chase(enemy,player);*/
}
void ShootState::shoot(Plane*enemy,Plane*player)
{
	//����ʧ�ܣ�ת��chase
	if(m_pFSM->shootPlayer(enemy,player) == false)
	{ 
		m_pFSM->chasePlayer(enemy,player);
		m_pFSM->setState(m_pFSM->getChaseState());
	}
}