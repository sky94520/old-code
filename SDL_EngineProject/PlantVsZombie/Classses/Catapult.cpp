#include "Catapult.h"
#include "ZombieBase.h"

Catapult::Catapult()
	:m_state(State::None),m_elapsed(0.f)
	,m_duration(0.f),m_pAimZombie(nullptr)
	,m_nDamage(0)
{
}

Catapult::~Catapult()
{
	//如果当前存在目标僵尸，则进行release
	SDL_SAFE_RELEASE_NULL(m_pAimZombie);
}

void Catapult::updateHook(float dt)
{
	//当前处于正常状态
	if (m_state == State::Normal)
	{
		//获取当前所在行
		int row = m_pCarrier->getRow();
		auto pos = this->getPosition();

		auto zombie = m_pDelegate->findFirstZombieOfRow(row,this->getDir(),pos);

		if (zombie != nullptr)
		{
			m_elapsed += dt;

			if (m_elapsed >= this->getColdDownTime())
			{
				auto animate = static_cast<Animate*>(this->getSprite()->getActionByTag(ANIMATION_TAG));
				int frameCount = animate->getAnimation()->getFrames().size();

				if (animate->getNextFrameIndex() == frameCount - 1)
				{
					m_elapsed = 0.f;
					this->changeState(State::Attack);

					m_pAimZombie = zombie;
					SDL_SAFE_RETAIN(m_pAimZombie);
				}
			}
		}
	}//处于攻击状态
	else if (m_state == State::Attack)
	{
		m_elapsed += dt;
		if (m_elapsed >= m_duration)
		{
			this->shoot();

			SDL_SAFE_RELEASE_NULL(m_pAimZombie);
			m_elapsed = 0.f;

			this->changeState(State::AttackEnd);
		}
	}//攻击结束
	else if (m_state == State::AttackEnd)
	{
		m_elapsed += dt;
		if (m_elapsed >= m_duration)
		{
			//攻击结束结束hook
			this->shootEndHook();

			m_elapsed = 0.f;
			this->changeState(State::Normal);
		}
	}
}
