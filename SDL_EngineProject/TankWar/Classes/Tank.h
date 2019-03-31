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
	//���ƣ���Ӧ��ͼ
	SDL_SYNTHESIZE(string, m_chartletName, ChartletName);
	//�ƶ��ٶ�
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
	//�ƶ�
	bool move(Direction dir);
	//վ��
	void sit();
	//���
	void fire();

	float changeState(State state);
};
#endif