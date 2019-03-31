#ifndef __DynamicData_H__
#define __DynamicData_H__
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;
#define RESSURECT_CSV_PATH "csv/playerressurect.csv"
#define LIFE_CSV_PATH "csv/playerlife.csv"
/*复活csv对应的属性*/
enum RessurectProp
{
	kRessurectProp_ID,
	kRessurectProp_Level,
	kRessurectProp_State,
	kRessurectProp_Worth,
};
/*生命csv对应的属性*/
enum LifeProp
{
	kLifeProp_ID,
	kLifeProp_Level,
	kLifeProp_State,
	kLifeProp_Worth,
};
class DynamicData
{
	SDL_SYNTHESIZE(int,m_nPlayerLives,PlayerLives);//主角生命
	SDL_SYNTHESIZE(int,m_nPlayerMaxHp,PlayerMaxHp);//主角的最大生命值
	SDL_SYNTHESIZE(float,m_nPlayerInvulnerableTime,PlayerInvulnerableTime);//主角的无敌时间
	SDL_SYNTHESIZE(float,m_playerSpeed,PlayerSpeed);//主角的移动速度
	SDL_SYNTHESIZE(int,m_gold,Gold);//主角金币

	SDL_SYNTHESIZE(int,m_lifeLevel,LifeLevel);//主角生命等级
	SDL_SYNTHESIZE(int,m_ressurectLevel,RessurectLevel);//主角复活的无敌等级
private:
	static DynamicData*m_pInstance;
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
	
	bool alterPlayerLives(int life);//增加或者减少生命值 同时会发送通知
	bool alterPlayerGold(int gold);//增加或者减少金币 同时会发生通知
	void reset();

	int getPlayerLives(int level);
	int getNextLifeLevel();//获取下一个等级，若当前已经到达最后一个，返回-1
	int getWorthByLifeLevel(int curLifeLevel);//根据当前的生命等级获得价值
};
#endif