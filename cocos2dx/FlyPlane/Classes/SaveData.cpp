#include "SaveData.h"
SaveData*SaveData::m_saveData = NULL;

SaveData*SaveData::getInstance()
{
	if(m_saveData == NULL)
	{
		m_saveData = new SaveData();
		if(m_saveData && m_saveData->init())
		{
			m_saveData->autorelease();
			m_saveData->retain();
		}
		else
		{
			CC_SAFE_DELETE(m_saveData);
			m_saveData = NULL;
		}
	}
	return m_saveData;
}
SaveData::SaveData()
{
}
SaveData::~SaveData()
{
}
bool SaveData::init()
{
	this->m_gold = 0;
	this->m_score = 0;

	return true;
}
long SaveData::getGold()
{
	return this->m_gold;
}
void SaveData::setGold(long iGold)
{
	this->m_gold = iGold;
}
long SaveData::getScore()
{
	return this->m_score;
}
void SaveData::setScore(long iScore)
{
	this->m_score = iScore;
}