#include "EnemyStateFSM.h"
#include "EnemyState.h"
#include "Plane.h"

EnemyStateFSM::EnemyStateFSM()
	:m_pChaseState(nullptr),m_pFleeState(nullptr)
	,m_pShootState(nullptr),m_pCurState(nullptr)
{
}
EnemyStateFSM::~EnemyStateFSM()
{
	SDL_SAFE_DELETE(m_pChaseState);
	SDL_SAFE_DELETE(m_pFleeState);
	SDL_SAFE_DELETE(m_pShootState);
}
bool EnemyStateFSM::init()
{
	m_pChaseState = new ChaseState(this);
	m_pFleeState = new FleeState(this);
	m_pShootState = new ShootState(this);

	m_pCurState = m_pChaseState;

	return true;
}
void EnemyStateFSM::chase(Plane*enemy,Plane*player)
{
	m_pCurState->chase(enemy,player);
}
void EnemyStateFSM::flee(Plane*enemy,Plane*player)
{
	m_pCurState->flee(enemy,player);
}
void EnemyStateFSM::shoot(Plane*enemy,Plane*player)
{
	m_pCurState->shoot(enemy,player);
}

void EnemyStateFSM::setState(EnemyState*state)
{
	m_pCurState = state;
}
EnemyState*EnemyStateFSM::getChaseState()const
{
	return m_pChaseState;
}
EnemyState*EnemyStateFSM::getFleeState()const
{
	return m_pFleeState;
}
EnemyState*EnemyStateFSM::getShootState()const
{
	return m_pShootState;
}
void EnemyStateFSM::chasePlayer(Plane*enemy,Plane*player)
{
	//׷�������ǰѷɻ��ĽǶȵ�����player���ڵ�λ��
	Point delta = player->getPosition() - enemy->getPosition();
	float degree = atan2(delta.y,delta.x);
	//ת��Ϊ�Ƕ�
	float angle = SDL_DEGREE_TO_ANGLE(degree);
	RotateTo*rotate = RotateTo::create(abs(angle)/90.f,angle);
	//������ת����
	enemy->getSprite()->stopAllActions();
	enemy->getSprite()->runAction(rotate);
}
bool EnemyStateFSM::shootPlayer(Plane*enemy,Plane*player)
{
	//ֻ�ел���������[-10,10]���Ż᳢�����
	/*auto delta = player->getPosition() - enemy->getPosition();
	float degree = atan2(delta.x,delta.y);
	float angle = SDL_DEGREE_TO_ANGLE(degree);

	if(abs(enemy->getSprite()->getRotation() - angle) <= 50.f)*/
		return enemy->shoot();
}