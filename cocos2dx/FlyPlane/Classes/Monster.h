#ifndef __Monster_H__
#define __Monster_H__
#include "Entity.h"

class Monster : public Entity
{
public:
	CREATE_FUNC(Monster);
	virtual bool init();
	Monster();
	~Monster();
public:
	void show();
	void hide();
	void reset();
	bool isAlive();

	int getSpeed();
	void setSpeed(int iSpeed);

	void run(Action*act);
private:
	bool m_isAlive;
	int m_speed;
};
#endif