#ifndef __FumeShroom_H__
#define __FumeShroom_H__
#include<string>
#include "FireShroom.h"
using namespace std;
class ZombieBase;

class FumeShroom : public FireShroom
{
private:
	float m_elapsed;
	float m_duration;
	bool m_bShooting;//是否应景发射子弹了
public:
	FumeShroom();
	~FumeShroom();

	static FumeShroom*create(const string&plantName);
	bool init(const string&plantName);
protected:
	virtual void updateAtkState(float dt);
	virtual void changeState(State state);
private:
	void shoot();
};
#endif