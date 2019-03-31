#ifndef __SnowMan_H__
#define __SnowMan_H__
#include<string>
#include "Plant.h"
using namespace std;

class SnowMan : public Plant
{
	SDL_SYNTHESIZE(int,m_nDamage,Damage);//…À∫¶÷µ
public:
	SnowMan();
	~SnowMan();
	static SnowMan*create(const string&plantName);
	bool init(const string&plantName);

	virtual void updateHook(float dt);
};
#endif