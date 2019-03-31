#include "Pea.h"
#include "ZombieBase.h"

Pea::Pea()
	:_elapsed(0.f),m_nDamage(0)
	,m_state(State::Normal),m_nBulletNumber(0)
{
}

Pea::~Pea()
{
}

void Pea::updateHook(float dt)
{
	if (m_state == State::Normal)
	{
		this->updateNormal(dt);
	}
	else if (m_state == State::Attack)
	{
		updateAttackState(dt);
	}
	else if (m_state == State::AttackEnd)
	{
		updateAttackEndState(dt);
	}
}

ZombieBase* Pea::findFirstZombie()
{
	//��ȡ��ǰ������
	int row = m_pCarrier->getRow();
	auto zombie = m_pDelegate->findFirstZombieOfRow(row,this->getDir(),this->getPosition());

	return zombie;
}

void Pea::changeState(State state)
{
	if (m_state == state)
		return ;
	m_state = state;
}

void Pea::updateNormal(float dt)
{
	auto zombie = findFirstZombie();
	//��ʬ���ڲ��һ�û������������й�������ʱ
	if (zombie != nullptr && !zombie->isDead())
	{
		_elapsed += dt;
		//���﹥��ʱ��
		if (_elapsed > this->getColdDownTime())
		{
			_elapsed -= this->getColdDownTime();
			//ת������״̬
			this->changeState(State::Attack);
		}
	}
	else
	{
		_elapsed = 0.f;
	}
}

void Pea::shootPeaBullet(int row,bool bRight)
{
	Point startPos = this->getPosition();
	Size size = this->getContentSize();
	//�Է����λ�ý���ȷ��
	startPos.x += size.width/2.f;
	startPos.y -= size.height/4.f;
	//����㶹�ӵ�
	this->shootPeaBullet(row,startPos,bRight);
}

void Pea::shootPeaBullet(int row,const Point&startPos,bool bRight)
{
	int damage = this->getDamage();
	m_pDelegate->addPeaBullet(damage,row,startPos,bRight);
}

void Pea::shootSnowPea(int row)
{
	int damage = this->getDamage();
	Point startPos = this->getPosition();
	Size size = this->getContentSize();
	//�Է����λ�ý���ȷ��
	startPos.x += size.width/2.f;
	startPos.y -= size.height/4.f;
	//��Ӻ����㶹�ӵ�
	m_pDelegate->addSnowPeaBullet(damage,row,startPos);
}

void Pea::shootFirePeaBullet(int row)
{
	int damage = this->getDamage();
	Point startPos = this->getPosition();
	Size size = this->getContentSize();
	//�Է����λ�ý���ȷ��
	startPos.x += size.width;
	startPos.y += size.height/4.f;
	//��ӻ��㶹�ӵ�
	m_pDelegate->addFirePeaBullet(damage,row,startPos);

}