#ifndef __Enemy_H__
#define __Enemy_H__
#include "Plane.h"
class EnemyStateFSM;

class Enemy:public Plane
{
private:
	float m_elapsed;
	 Plane*m_pPlayer;
	EnemyStateFSM*m_pFSM;
public:
	Enemy();
	~Enemy();
	static Enemy*create(Plane*player);
	bool init(Plane*player);
	void flee();//Ã”¿Î

	virtual void update(float dt);
	virtual void onDead();
};
#endif