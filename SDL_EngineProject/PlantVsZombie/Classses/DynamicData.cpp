#include "DynamicData.h"
DynamicData*DynamicData::m_pInstance = nullptr;
DynamicData::DynamicData()
	:m_soundVolume(1.f),m_musicVolume(1.f)
	,m_nSunNumber(0),m_nCardVesselNum(0)
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
	//todo
	//获取卡槽个数
	m_nCardVesselNum = UserDefault::getInstance()->getIntegerForKey("card-vessel-num",6);

	string sPlant = "LilyPad,FlowerPot,SunFlower,CoffeeBean,Peashooter,Repeater,Threepeater,GatlingPea";
	//string sPlant = "LilyPad,FlowerPot,SunFlower,CoffeeBean";
	
	auto plantStr = UserDefault::getInstance()->getStringForKey("plant",sPlant);
	//进行字符串的解析
	auto vec = StringUtils::split(plantStr,',');
	for (auto v:vec)
	{
		m_plants.push_back(v.asString());
	}
	//僵尸卡片
	string sZombie = "Zombie";
	m_zombieCards.push_back("Zombie");
	m_zombieCards.push_back("ConeheadZombie");
	m_zombieCards.push_back("PaperZombie");
	m_zombieCards.push_back("PoleVaultingZombie");
	m_zombieCards.push_back("BucketheadZombie");
	m_zombieCards.push_back("FootballZombie");
	m_zombieCards.push_back("ScreenDoorZombie");
	m_zombieCards.push_back("BackupDancer");
	m_zombieCards.push_back("DancingZombie");

	return true;
}

void DynamicData::purge()
{
	SDL_SAFE_DELETE(m_pInstance);
}

vector<string>& DynamicData::getNameOfPlantCards()
{
	return m_plants;
}

vector<string>& DynamicData::getNameOfZombieCards()
{
	return m_zombieCards;
}