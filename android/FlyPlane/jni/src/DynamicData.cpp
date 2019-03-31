#include "DynamicData.h"

DynamicData*DynamicData::m_pInstance = nullptr;

DynamicData::DynamicData()
	:m_nScore(0),m_nLife(0),m_nScorePerLife(0)
{
	m_nLife = 2;
}
DynamicData::~DynamicData()
{
}
void DynamicData::purge()
{
	SDL_SAFE_DELETE(m_pInstance);
	m_pInstance = nullptr;
}
void DynamicData::alterScore(int score)
{
	m_nScore += score;
	m_nScorePerLife += score;
	if(m_nScorePerLife >= 100)
	{
		m_nScorePerLife -= 100;
		m_nLife += 1;
	}
	//发送给观察者
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("dynamic data");
}
void DynamicData::alterLife(int life)
{
	m_nLife += life;
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("dynamic data");
}
void DynamicData::reset()
{
	m_nLife = 2;
	m_nScore = 0;
	m_nScorePerLife = 0;
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("dynamic data");
}