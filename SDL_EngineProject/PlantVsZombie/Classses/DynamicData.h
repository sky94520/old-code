#ifndef __DynamicData_H__
#define __DynamicData_H__
#include<vector>
#include<string>
#include "SDL_Engine/SDL_Engine.h"

using namespace std;
using namespace SDL;
class DynamicData:public Object
{
	//作保留使用
	SDL_SYNTHESIZE(float,m_soundVolume,SounVolume);//音效 [0,1]
	SDL_SYNTHESIZE(float,m_musicVolume,MusicVolume);//音乐 [0,1]

	SDL_SYNTHESIZE(int,m_nSunNumber,SunNumber);//太阳数量
	SDL_SYNTHESIZE(unsigned int,m_nCardVesselNum,CardVesselNum);//卡槽个数
private:
	static DynamicData*m_pInstance;
	vector<string> m_plants;//拥有的植物名称数组
	vector<string> m_zombieCards;//拥有的僵尸卡片
private:
	DynamicData();
	~DynamicData();
public:
	static DynamicData*getInstance();
	bool init();
	void purge();
	//获取拥有的植物数组
	vector<string>& getNameOfPlantCards();
	//获取拥有的僵尸卡片数组
	vector<string>& getNameOfZombieCards();
};
#endif