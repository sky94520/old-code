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
	//射击成功,跳转状态
	if(m_pFSM->shootPlayer(enemy,player))
		m_pFSM->setState(m_pFSM->getShootState());
	else//射击失败，追击
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
	//逃跑，就是把飞机的角度调整和player所在的位置
	Point delta = player->getPosition() - enemy->getPosition();
	float degree = atan2(delta.y,delta.x);
	//转化为角度
	float angle = SDL_DEGREE_TO_ANGLE(degree);
	if(angle > 0)
		angle = 180 - angle;
	else if(angle < 0)
		angle = abs(angle) - 180;

	RotateTo*rotate = RotateTo::create(abs(angle/90.f),angle);
	//运行旋转动画
	enemy->getSprite()->stopAllActions();
	enemy->getSprite()->runAction(rotate);
}
void FleeState::shoot(Plane*enemy,Plane*player)
{
	//逃离状态下不会尝试射击
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
	//发射失败，转到chase
	if(m_pFSM->shootPlayer(enemy,player) == false)
	{ 
		m_pFSM->chasePlayer(enemy,player);
		m_pFSM->setState(m_pFSM->getChaseState());
	}
}