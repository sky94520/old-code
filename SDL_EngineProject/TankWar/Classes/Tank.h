#ifndef __Tank_H__
#define __Tank_H__
#include <string>
#include "Entity.h"

using namespace std;

enum class Direction;
enum class State
{
	Idle,
	Run,
	Fire,
};

class Tank : public Entity
{
	//名称，对应贴图
	SDL_SYNTHESIZE(string, m_chartletName, ChartletName);
	//移动速度
	SDL_SYNTHESIZE(float, m_speed, Speed);
private:
	Direction m_dir;
	State m_state;
	bool _dirty;
public:
	Tank();
	~Tank();

	static Tank* create(const string& name);
	bool init(const string& name);
	//移动
	bool move(Direction dir);
	//站立
	void sit();
	//射击
	void fire();

	float changeState(State state);
};
#endif