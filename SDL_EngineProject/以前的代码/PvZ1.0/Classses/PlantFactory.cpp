#include "PlantFactory.h"
PlantFactory*PlantFactory::m_pInstance = nullptr;
PlantFactory::PlantFactory()
{
}
PlantFactory::~PlantFactory()
{
	for(auto iter:m_creators)
	{
		auto creator = iter.second;
		delete creator;
	}
	m_creators.clear();
}
void PlantFactory::purge()
{
	SDL_SAFE_DELETE(m_pInstance);
}
bool PlantFactory::registerType(const std::string&type,BaseCreator*pCreator)
{
	auto iter = m_creators.find(type);
	//不存在，则保存创造器
	if(iter == m_creators.end())
	{
		m_creators[type] = pCreator;
		return true;
	}
	return false;
}
Plant*PlantFactory::create(const std::string&type)const
{
	auto iter = m_creators.find(type);
	//已找到对应创造器
	if(iter != m_creators.end())
	{
		auto pCreator = iter->second;
		return pCreator->createObject();
	}
	return nullptr;
}