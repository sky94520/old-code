#include "DynamicData.h"
#include "CsvUtil.h"
DynamicData*DynamicData::m_pInstance = nullptr;
DynamicData::DynamicData()
	:m_nPlayerLives(0),m_nPlayerMaxHp(1),m_gold(0)
	,m_nPlayerInvulnerableTime(0.f),m_playerSpeed(0.f)
	,m_lifeLevel(0),m_ressurectLevel(0)
{
	//读取外部文件获取相关数据
	m_playerSpeed = UserDefault::getInstance()->getFloatForKey("speed",1.5f);
	m_gold = UserDefault::getInstance()->getIntegerForKey("gold",0);
	//读取文件
	m_lifeLevel = UserDefault::getInstance()->getIntegerForKey("life-level",0);
	m_ressurectLevel = UserDefault::getInstance()->getIntegerForKey("ressurect-level",0);
	//主角生命
	int line1 = CsvUtil::getInstance()->findLineByValue(Value(m_lifeLevel),kLifeProp_Level,LIFE_CSV_PATH);
	m_nPlayerLives = CsvUtil::getInstance()->getValue(line1,kLifeProp_State,LIFE_CSV_PATH).asInt();
	//无敌时间
	int line2 = CsvUtil::getInstance()->findLineByValue(Value(m_ressurectLevel),kRessurectProp_Level,RESSURECT_CSV_PATH);
	m_nPlayerInvulnerableTime = CsvUtil::getInstance()->getValue(line2,kRessurectProp_State,RESSURECT_CSV_PATH).asFloat();
}
DynamicData::~DynamicData()
{
	UserDefault::getInstance()->setIntegerForKey("gold",m_gold);
	UserDefault::getInstance()->setIntegerForKey("life-level",m_lifeLevel);
	UserDefault::getInstance()->setIntegerForKey("ressurect-level",m_ressurectLevel);
}
void DynamicData::purge()
{
	SDL_SAFE_DELETE(m_pInstance);
}
bool DynamicData::alterPlayerLives(int life)
{
	//游戏是否继续
	bool bContinue = false;
	int lives = m_nPlayerLives + life;
	if(lives >= 0)
		bContinue = true;
	else
		lives = 0;
	m_nPlayerLives = lives;
	//发出通知
	NotificationCenter::getInstance()->postNotification("dynamic data",nullptr);
	return bContinue;
}
bool DynamicData::alterPlayerGold(int gold)
{
	bool bRet = false;
	int curGold = m_gold + gold;
	if(curGold >= 0)
		bRet = true;
	else
		curGold = 0;
	m_gold = curGold;
	//发出通知
	NotificationCenter::getInstance()->postNotification("dynamic data",nullptr);
	return true;
}
void DynamicData::reset()
{
	//主角生命
	int line1 = CsvUtil::getInstance()->findLineByValue(Value(m_lifeLevel),kLifeProp_Level,LIFE_CSV_PATH);
	m_nPlayerLives = CsvUtil::getInstance()->getValue(line1,kLifeProp_State,LIFE_CSV_PATH).asInt();
}
int DynamicData::getPlayerLives(int level)
{
	int line = CsvUtil::getInstance()->findLineByValue(Value(m_lifeLevel+1),kLifeProp_Level,LIFE_CSV_PATH);
	return CsvUtil::getInstance()->getValue(line,kLifeProp_State,LIFE_CSV_PATH).asInt();
}
int DynamicData::getNextLifeLevel()
{
	//判断是否存在下一等级
	int nextLine = CsvUtil::getInstance()->findLineByValue(Value(m_lifeLevel+1),kLifeProp_Level,LIFE_CSV_PATH);
	if(nextLine >= 0)
		return CsvUtil::getInstance()->getValue(nextLine,kLifeProp_Level,LIFE_CSV_PATH).asInt();
	return -1;
}
int DynamicData::getWorthByLifeLevel(int curLifeLevel)
{
	int curLine = CsvUtil::getInstance()->findLineByValue(Value(curLifeLevel),kLifeProp_Level,LIFE_CSV_PATH);
	if(curLine >= 0)
		return CsvUtil::getInstance()->getValue(curLine,kLifeProp_Worth,LIFE_CSV_PATH).asInt();
	return -1;
}