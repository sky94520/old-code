#include "DynamicData.h"
DynamicData*DynamicData::m_pInstance = nullptr;
DynamicData::DynamicData()
	:m_soundVolume(true),m_musicVolume(false),m_nScore(0)
	,m_bulletDuration(0.f),m_nPlayerLives(1)
{
}
DynamicData::~DynamicData()
{
}
DynamicData*DynamicData::getInstance()
{
	if(m_pInstance == nullptr)
	{
		m_pInstance = new DynamicData();
		m_pInstance->init();
	}
	return m_pInstance;
}
bool DynamicData::init()
{
	//∂¡»°µ±«∞“Ù¿÷
	//todo
	return true;
}
void DynamicData::purge()
{
	CC_SAFE_DELETE(m_pInstance);
}
void DynamicData::alertScore(int nScore)
{
	m_nScore += nScore;
}
void DynamicData::save()
{
}