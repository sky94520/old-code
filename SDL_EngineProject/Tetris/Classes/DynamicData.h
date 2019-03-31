#ifndef __DynamicData_H__
#define __DynamicData_H__
#include "SDL_Engine/SDL_Engine.h"

using namespace SDL;
class DynamicData
{
	SDL_SYNTHESIZE(int,m_nLevel,Level);//当前级别
	SDL_SYNTHESIZE(int,m_nScore,Score);//当前分数
private:
	static DynamicData*m_pInstance;
	int m_nLevelUpLine;//还剩多少行升级
private:
	DynamicData();
	~DynamicData();
public:
	static DynamicData*getInstance()
	{
		if(m_pInstance == nullptr)
			m_pInstance = new DynamicData();
		return m_pInstance;
	}
	void purge();
	void reset();
	void alterScore(int brickLines);//增加分数,并发送消息，同时判断是否应该升级和改变速度
	float getIntervalByLevel()const;//通过当前等级获得interval
};
#endif