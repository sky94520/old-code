#include "Global.h"
#include "MonsterManager.h"
Global*Global::g_pInstance = nullptr;
Global::Global()
{
	_monsterManager = nullptr;
}
Global::~Global()
{
}
Global*Global::getInstance()
{
	if(g_pInstance == nullptr)
		g_pInstance = new Global();
	return g_pInstance;
}