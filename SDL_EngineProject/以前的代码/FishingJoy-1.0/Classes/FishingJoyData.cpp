#include "FishingJoyData.h"
FishingJoyData*FishingJoyData::m_pInstance = nullptr;
FishingJoyData::FishingJoyData()
	:m_nGold(100),m_soundVolume(1.f),m_musicVolume(1.f)
{
}
FishingJoyData::~FishingJoyData()
{
	//保存当前金币数目
	UserDefault::getInstance()->setIntegerForKey("gold",m_nGold);
	UserDefault::getInstance()->setIntegerForKey("BulletCountType1",m_nBulletCount_1);
	UserDefault::getInstance()->setIntegerForKey("BulletCountType2",m_nBulletCount_2);
}
FishingJoyData*FishingJoyData::getInstance()
{
	if(m_pInstance == nullptr)
	{
		m_pInstance = new FishingJoyData();
		m_pInstance->init();
	}
	return m_pInstance;
}
bool FishingJoyData::init()
{
	//读取金币数量
	m_nGold = UserDefault::getInstance()->getIntegerForKey("gold",200);
	//获取相应弹药的数目
	m_nBulletCount_1 = UserDefault::getInstance()->getIntegerForKey("BulletCountType1",999);
	m_nBulletCount_2 = UserDefault::getInstance()->getIntegerForKey("BulletCountType2",10);

	return true;
}
void FishingJoyData::purge()
{
	SDL_SAFE_DELETE(m_pInstance);
}
void FishingJoyData::save()
{
}
void FishingJoyData:: alterGold(Value value,bool bAdd)
{
	if(bAdd)
		NotificationCenter::getInstance()->postNotification("add coin",&value);
	else
		NotificationCenter::getInstance()->postNotification("sub coin",&value);
}
int FishingJoyData::getBulletCountByType(BulletType type)
{
	int count = 0;
	switch(type)
	{
	case BulletType::kBulletType_1:count = m_nBulletCount_1;break;
	case BulletType::kBulletType_2:count = m_nBulletCount_2;break;
	}
	return count;
}
void FishingJoyData::setBulletCountByType(BulletType type,int count)
{
	switch(type)
	{
	case BulletType::kBulletType_1:m_nBulletCount_1 = count;break;
	case BulletType::kBulletType_2:m_nBulletCount_2 = count;break;
	}
}