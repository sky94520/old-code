#include "Skill.h"
Skill::Skill()
	:m_name(NULL),m_desc(NULL)
{
}
Skill::~Skill()
{
}
bool Skill::load(LPCWSTR name,LPCWSTR desc)
{
	m_name = name;
	m_desc = desc;

	return true;
}
LPCWSTR Skill::getName()const
{
	return m_name;
}
LPCWSTR Skill::getDesc()const
{
	return m_desc;
}