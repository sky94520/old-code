#include "DynamicData.h"
DynamicData*DynamicData::m_pInstance = nullptr;
DynamicData::DynamicData()
	:m_soundVolume(1.f),m_musicVolume(1.f)
	,m_nSunNumber(0)
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
	//读取文件，默认太阳为50
	m_nSunNumber = UserDefault::getInstance()->getIntegerForKey("sun",200);
	return true;
}
void DynamicData::purge()
{
	SDL_SAFE_DELETE(m_pInstance);
}
void DynamicData::alertSunNum(int num)
{
	//更改太阳数量 最大数量 999
	m_nSunNumber += num;
	if(m_nSunNumber > 999)
		m_nSunNumber = 999;
	NotificationCenter::getInstance()->postNotification("sunshine",nullptr);
}