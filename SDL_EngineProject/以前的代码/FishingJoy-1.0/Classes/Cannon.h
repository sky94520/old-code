#ifndef __Cannon_H__
#define __Cannon_H__
#include<cmath>
#include "Entity.h"
#define PI 3.1415926535898
typedef enum
{
	kCannonType_1 = 1,
	kCannonType_2,
	kCannonType_3,
	kCannonType_4,
	kCannonType_5,
	kCannonType_6,
	kCannonType_7
}CannonType;
class Cannon:public Entity
{
private:
	CannonType m_kCannonType;//炮塔等级

public:
	Cannon();
	~Cannon();
	CREATE_FUNC(Cannon);
	bool init();
public:
	//炮台朝向
	void aimAt(const Point &target);
	void addLevel();
	void subLevel();
	//获取炮台类型
	CannonType getCannonType()const;
	//获取炮台发射的长度
	float getRouteDistance()const;
private:
	void setType(CannonType type);
};
#endif