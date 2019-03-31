#include "DynamicData.h"
DynamicData*DynamicData::m_pInstance = nullptr;

DynamicData::DynamicData()
	:m_score(0),m_coin(0)
	,m_life(0),m_remainTime(0)
{
}
DynamicData::~DynamicData()
{
}
void DynamicData::purge()
{
	if(m_pInstance)
		SDL_SAFE_DELETE(m_pInstance);
}
bool DynamicData::init()
{
	this->alterTime(300);
	this->alterLife(3);

	return true;
}
void DynamicData::alterScore(int score)
{
	m_score += score;
	//增加人物生命
	if(m_score >= 10000)
	{
		m_score -= 10000;
		this->alterLife(1);
	}
	//发送 分数事件
	_eventDispatcher->dispatchCustomEvent("score");
}
void DynamicData::alterCoin(int coin)
{
	m_coin += coin;
	if(m_coin >= 100)
	{
		m_coin -= 100;
		this->alterLife(1);
	}
	_eventDispatcher->dispatchCustomEvent("coin");
}
void DynamicData::alterLife(int life)
{
	m_life += life;
	_eventDispatcher->dispatchCustomEvent("life");
}
void DynamicData::alterTime(int time)
{
	m_remainTime += time;
	_eventDispatcher->dispatchCustomEvent("time");
}