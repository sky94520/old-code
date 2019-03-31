#include "StaticData.h"
StaticData*StaticData::m_pInstance = nullptr;
StaticData::StaticData()
{
}
StaticData::~StaticData()
{
}
StaticData*StaticData::getInstance()
{
	if(m_pInstance == nullptr)
	{
		m_pInstance = new StaticData();
		m_pInstance->init();
	}
	return m_pInstance;
}
void StaticData::purge()
{
	CC_SAFE_DELETE(m_pInstance);
}
bool StaticData::init()
{
	m_valueMap = FileUtils::getInstance()->getValueMapFromFile("utf8_char.plist");
	return true;
}
Value StaticData::getValueForKey(const std::string&key)const
{
	return m_valueMap.at(key);
}
std::string StaticData::getStringForKey(const std::string&key)const
{
	return getValueForKey(key).asString();
}