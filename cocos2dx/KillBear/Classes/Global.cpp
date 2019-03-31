#include "Global.h"
Global*Global::m_pInstance = NULL;
Global::Global()
{
	m_pHero = NULL;
	m_pOperatorLayer = NULL;
	m_pStateLayer = NULL;
	m_pRocker = NULL;
	m_pGameLayer = NULL;
}
Global::~Global()
{
}