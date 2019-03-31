#ifndef __DynamicData_H__
#define __DynamicData_H__
#include<string>
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;
using namespace std;

class DynamicData:public Layer
{
	SDL_SYNTHESIZE(int,m_score,Score);
	SDL_SYNTHESIZE(int,m_coin,Coin);
	SDL_SYNTHESIZE(int,m_life,Life);
	SDL_SYNTHESIZE(int,m_remainTime,RemainTime);
private:
	static DynamicData*m_pInstance;
	DynamicData();
	~DynamicData();
private:
/*	int m_score;//当前的分数
	int m_coin;//当前的金币
	int m_life;//当前的生命
	int m_remainTime;//剩余时间*/
public:
	static DynamicData*getInstance()
	{
		if(m_pInstance == nullptr)
		{
			m_pInstance = new DynamicData();
		}
		return m_pInstance;
	}
	static void purge();
	bool init();
	//修改分数，一边增加分数 传送给PanelLayer
	void alterScore(int score);
	void alterCoin(int coin);
	void alterLife(int life);
	void alterTime(int time);
/*
	int getScore()const{return m_score;}
	int getCoin()const{return m_coin;}
	int getLife()const{return m_life;}
	int getRemantTime()const{return m_remainTime;}*/
};
#endif