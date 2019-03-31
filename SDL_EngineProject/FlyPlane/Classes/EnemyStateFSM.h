#ifndef __EnemyStateFSM_H__
#define __EnemyStateFSM_H__
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;

class EnemyState;
class Plane;

class EnemyStateFSM:public Object
{
private:
	EnemyState*m_pChaseState;
	EnemyState*m_pFleeState;
	EnemyState*m_pShootState;

	EnemyState*m_pCurState;
public:
	EnemyStateFSM();
	~EnemyStateFSM();
	CREATE_FUNC(EnemyStateFSM);
	bool init();

	void chase(Plane*enemy, Plane*player);
	void flee(Plane*enemy, Plane*player);
	void shoot(Plane*enemy, Plane*player);

	void setState(EnemyState*state);
	EnemyState*getChaseState()const;
	EnemyState*getFleeState()const;
	EnemyState*getShootState()const;
	
	void chasePlayer(Plane*enemy,Plane*player);
	bool shootPlayer(Plane*enemy,Plane*player);
};
#endif