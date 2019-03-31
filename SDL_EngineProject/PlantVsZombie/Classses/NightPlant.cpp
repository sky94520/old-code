#include "NightPlant.h"

NightPlant::NightPlant()
	:m_bSleeping(false)
{
}

NightPlant::~NightPlant()
{
}

void NightPlant::enterSleeping()
{
	m_bSleeping = true;

	onSleepingEnter();
}

void NightPlant::exitSleeping()
{
	m_bSleeping = false;

	onSleepingExit();
}

void NightPlant::updateHook(float dt)
{
	if (!m_bSleeping)
	{
		updateNotSleeping(dt);
	}
}

bool NightPlant::isSleeping()const
{
	return m_bSleeping;
}