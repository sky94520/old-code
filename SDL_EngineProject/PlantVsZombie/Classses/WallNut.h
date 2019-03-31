#ifndef __WallNut_H__
#define __WallNut_H__
#include<string>
#include "Plant.h"
using namespace std;

class WallNut : public Plant
{
protected:
	enum class State
	{
		None,
		Normal,
		Cracked1,
		Cracked2,
	};
protected:
	State m_state;
public:
	WallNut();
	~WallNut();
	static WallNut*create(const string&plantName);
	bool init(const string&plantName);

	virtual void updateHook(float dt);
	virtual void onHurt();
protected:
	virtual void changeState(State state);
};
#endif