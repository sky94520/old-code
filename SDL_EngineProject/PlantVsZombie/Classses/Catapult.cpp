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
	//�����ǰ����Ŀ�꽩ʬ�������release
	SDL_SAFE_RELEASE_NULL(m_pAimZombie);
}

void Catapult::updateHook(float dt)
{
	//��ǰ��������״̬
	if (m_state == State::Normal)
	{
		//��ȡ��ǰ������
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
	}//���ڹ���״̬
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
	}//��������
	else if (m_state == State::AttackEnd)
	{
		m_elapsed += dt;
		if (m_elapsed >= m_duration)
		{
			//������������hook
			this->shootEndHook();

			m_elapsed = 0.f;
			this->changeState(State::Normal);
		}
	}
}
