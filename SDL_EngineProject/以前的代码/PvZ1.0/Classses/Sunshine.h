#ifndef __Sunshine_H__
#define __Sunshine_H__
#include "Entity.h"
typedef enum SunshineType
{
	kSunshineType_15 = 15,//15
	kSunshineType_25 = 25
}SunshineType;
class Sunshine:public Entity
{
	SDL_SYNTHESIZE(float,m_elapsed,Elapsed);//流逝值
	SDL_SYNTHESIZE(SunshineType,m_type,SunshineType);//太阳类型
private:
	bool m_bArriveLawn;//是否到达地面
	bool m_bCollected;//是否被收集
public:
	Sunshine();
	~Sunshine();
	static Sunshine*create(SunshineType type);
	bool init(SunshineType type);

	bool isArriveLawn()const;
	void setArriveLawn(bool ret);

	bool isCollected()const;
	void setCollected(bool collected);
};
#endif