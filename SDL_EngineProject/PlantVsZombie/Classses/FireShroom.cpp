#include "FireShroom.h"
#include "ZombieBase.h"

FireShroom::FireShroom()
	:m_attackScope(0.f),m_nDamage(0)
	,m_state(State::Normal),_elapsed(0.f)
{
}

FireShroom::~FireShroom()
{
}

void FireShroom::updateNotSleeping(float dt)
{
	if (m_state == State::Normal)
	{
		this->updateNormalState(dt);
	}
	else if (m_state == State::Attack)
	{
		this->updateAtkState(dt);
	}
}

void FireShroom::onSleepingEnter()
{
	this->changeState(State::Sleeping);
}

void FireShroom::onSleepingExit()
{
	this->changeState(State::Normal);
}

void FireShroom::updateNormalState(float dt)
{
	auto row = m_pCarrier->getRow();
	auto attackDir = this->getDir();
	auto pos = this->getPosition();
	//���ݵ�ǰ����ȷ����һ����ʬ
	auto zombie = m_pDelegate->findFirstZombieOfRow(row,attackDir,pos);

	if (zombie == nullptr)
		return;

	auto zombiePos = zombie->getPosition();

	auto distance = zombiePos.x - pos.x;
	//�ڹ�����Χ�ڣ���ʼ����5
	if (distance <= m_attackScope)
	{
		_elapsed += dt;
		//���й���
		if (_elapsed >= this->getColdDownTime())
		{
			_elapsed -= this->getColdDownTime();
			//ת�빥��״̬
			this->changeState(State::Attack);
		}
	}
}