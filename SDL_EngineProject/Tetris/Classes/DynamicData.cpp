#include "DynamicData.h"
DynamicData*DynamicData::m_pInstance = nullptr;

DynamicData::DynamicData()
	:m_nLevel(1),m_nScore(0)
	,m_nLevelUpLine(20)
{
}
DynamicData::~DynamicData()
{
}
void DynamicData::purge()
{
	SDL_SAFE_DELETE(m_pInstance);
}
void DynamicData::reset()
{
	m_nLevel = 1;
	m_nScore = 0;
	m_nLevelUpLine = 20;
	NotificationCenter::getInstance()->postNotification("DynamicData",nullptr);
}
void DynamicData::alterScore(int brickLines)
{
	int score = 0;
	switch(brickLines)
	{
	case 1:score = 40;break;
	case 2:score = 100;break;
	case 3:score = 300;break;
	case 4:score = 1200;break;
	}
	m_nScore += score;
	m_nLevelUpLine -= brickLines;
	if(m_nLevelUpLine <= 0)
	{
		m_nLevel++;
		m_nLevelUpLine += 20;
	}
	NotificationCenter::getInstance()->postNotification("DynamicData",nullptr);
}
float DynamicData::getIntervalByLevel()const
{
	return 1.f - m_nLevel*0.1f;
}
