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
	//获取当前所在行
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
	//僵尸存在并且还没有死亡，则进行攻击倒计时
	if (zombie != nullptr && !zombie->isDead())
	{
		_elapsed += dt;
		//到达攻击时间
		if (_elapsed > this->getColdDownTime())
		{
			_elapsed -= this->getColdDownTime();
			//转到攻击状态
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
	//对发射的位置进行确定
	startPos.x += size.width/2.f;
	startPos.y -= size.height/4.f;
	//添加豌豆子弹
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
	//对发射的位置进行确定
	startPos.x += size.width/2.f;
	startPos.y -= size.height/4.f;
	//添加寒冰豌豆子弹
	m_pDelegate->addSnowPeaBullet(damage,row,startPos);
}

void Pea::shootFirePeaBullet(int row)
{
	int damage = this->getDamage();
	Point startPos = this->getPosition();
	Size size = this->getContentSize();
	//对发射的位置进行确定
	startPos.x += size.width;
	startPos.y += size.height/4.f;
	//添加火豌豆子弹
	m_pDelegate->addFirePeaBullet(damage,row,startPos);

}