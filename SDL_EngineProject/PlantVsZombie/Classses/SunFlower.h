#ifndef __SunFlower_H__
#define __SunFlower_H__
#include<string>
#include "Plant.h"
using namespace std;

class SunFlower : public Plant
{
public:
	enum class State
	{
		Normal,
		ProducingSun,
	};
protected:
	State m_curState;
	float m_produceSunDuration;//�������� ����ʱ��
	float m_elapsed;
public:
	SunFlower();
	~SunFlower();
	static SunFlower*create(const string&plantName);
	bool init(const string&plantName);

	//virtual void update(float dt);
	virtual void visit();
	virtual void updateHook(float dt);
protected:
	virtual void productSun();
};
//---------------------------------TwinSunflower------------------
class TwinSunflower : public SunFlower
{
public:
	TwinSunflower();
	~TwinSunflower();
	static TwinSunflower*create(const string&plantName);
	bool init(const string&plantName);

	virtual void updateHook(float dt);
protected:
	virtual void productSun();
};
#endif