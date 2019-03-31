#include "Garnishry.h"
#include "HpBar.h"
#include "Bullet.h"

Garnishry::Garnishry()
	:m_nMaxHitPoint(0),m_nHitPoint(0)
	,m_type(Type::Common),m_pHpBar(nullptr)
	,m_bImmuneForIce(false)
{
}

Garnishry::~Garnishry()
{
}

bool Garnishry::init(int hp)
{
	//设置血量
	this->setHitPoint(hp);
	this->setMaxHitPoint(hp);
	//添加血量条
	m_pHpBar = HpBar::create("hpBar2.png","hpBarBG.png",(float)hp);
	auto size = m_pHpBar->getContentSize();

	m_pHpBar->setPosition(size.width/2.f,size.height/2.f);

	this->addChild(m_pHpBar);
	this->setContentSize(size);

	return true;
}

int Garnishry::absorbDamage(int baseDamage,AttackType attackType)
{
	return baseDamage;
}

bool Garnishry::isImmuneForDeceleration(AttackType type)const
{
	return false;
}

bool Garnishry::isImmuneForButter()const
{
	return false;
}

int Garnishry::hurt(int damage)
{
	int afterDamage = 0;
	int afterHP = this->getHitPoint() - damage;
	//饰品即将死亡
	if (afterHP <= 0)
	{
		afterDamage = SDL_abs(afterHP);
		afterHP = 0;
	}
	this->setHitPoint(afterHP);
	m_pHpBar->setValue((float)afterHP);

	return afterDamage;
}
//----------------------------------Conehead---------------------
Conehead::Conehead()
{
}

Conehead::~Conehead()
{
}

Conehead*Conehead::create(int hp)
{
	auto good = new Conehead();

	if (good && good->init(hp))
		good->autorelease();
	else
		SDL_SAFE_DELETE(good);

	return good;
}

bool Conehead::init(int hp)
{
	if (Garnishry::init(hp))
	{
		this->setType(Type::Common);

		return true;
	}
	return false;
}

int Conehead::absorbDamage(int baseDamage,AttackType attackType)
{
	int afterDamage = this->hurt(baseDamage);

	return afterDamage;
}
//-------------------------Paper-------------------------------
Paper*Paper::create(int hp)
{
	auto paper = new Paper();

	if (paper && paper->init(hp))
		paper->autorelease();
	else
		SDL_SAFE_DELETE(paper);

	return paper;
}

bool Paper::init(int hp)
{
	if (Garnishry::init(hp))
	{
		this->setType(Type::Common);

		return true;
	}
	return false;
}

int Paper::absorbDamage(int baseDamage,AttackType attackType)
{
	int afterDamage = -1;
	//跟踪性子弹，无法吸收
	if (Bullet::isTrackBullet(attackType))
	{
		afterDamage = baseDamage;
	}
	//穿透性子弹，全部受伤
	else if (attackType == AttackType::Penetrate)
	{
		this->hurt(baseDamage);

		afterDamage = baseDamage;
	}
	else//吸收伤害
	{
		afterDamage = this->hurt(baseDamage);
	}

	return afterDamage;
}

bool Paper::isImmuneForDeceleration(AttackType attackType)const
{
	if (Bullet::isTrackBullet(attackType))
		return false;
	return true;
}
//----------------Pole撑杆----------------------------------
bool Pole::init()
{
	return true;
}

int Pole::absorbDamage(int baseDamage,AttackType attackType)
{
	//TODO
	return baseDamage;
}
//-------------------------Bucket------------------------------
Bucket*Bucket::create(int hp)
{
	auto bucket = new Bucket();

	if (bucket && bucket->init(hp))
		bucket->autorelease();
	else
		SDL_SAFE_DELETE(bucket);

	return bucket;
}

bool Bucket::init(int hp)
{
	if (Garnishry::init(hp))
	{
		this->setType(Type::Iron);
		return true;
	}
	return false;
}

int Bucket::absorbDamage(int baseDamage,AttackType attackType)
{
	int afterDamage = this->hurt(baseDamage);

	return afterDamage;
}
//-------------------------Helmet----------------------------
Helmet* Helmet::create(int hp)
{
	auto helmet = new Helmet();

	if (helmet && helmet->init(hp))
		helmet->autorelease();
	else
		SDL_SAFE_DELETE(helmet);

	return helmet;
}

bool Helmet::init(int hp)
{
	if (Garnishry::init(hp))
	{
		this->setType(Type::Iron);
		return true;
	}
	return false;
}

int Helmet::absorbDamage(int baseDamage,AttackType attackType)
{
	int afterDamage = this->hurt(baseDamage);

	return afterDamage;
}
//-------------------------ScreenDoor----------------------------
ScreenDoor* ScreenDoor::create(int hp)
{
	auto door = new ScreenDoor();

	if (door && door->init(hp))
		door->autorelease();
	else
		SDL_SAFE_DELETE(door);

	return door;
}

bool ScreenDoor::init(int hp)
{
	if (Garnishry::init(hp))
	{
		this->setType(Type::Iron);
		return true;
	}
	return false;
}

int ScreenDoor::absorbDamage(int baseDamage,AttackType attackType)
{
	int afterDamage = -1;
	//跟踪性子弹，无法吸收
	if (Bullet::isTrackBullet(attackType))
	{
		afterDamage = baseDamage;
	}
	//穿透性子弹，全部受伤
	else if (attackType == AttackType::Penetrate)
	{
		this->hurt(baseDamage);

		afterDamage = baseDamage;
	}
	else//吸收伤害
	{
		afterDamage = this->hurt(baseDamage);
	}

	return afterDamage;
}

bool ScreenDoor::isImmuneForDeceleration(AttackType attackType)const
{
	if (Bullet::isTrackBullet(attackType))
		return false;
	return true;
}