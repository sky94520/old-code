#include "Zombie.h"
#include "MainLua.h"
#include "HpBar.h"
#include "Plant.h"
Zombie::Zombie()
	:m_nHitPoint(0),m_nDefense(0),
	m_fSpeed(0.f),m_status(kZombieStatus_None)
	,m_pHpBar(nullptr),m_pHead(nullptr),m_fSkillTime(0.f)
	,m_showTime(0.f),m_elapsed(0.f),m_nRoute(0)
{
}
Zombie::~Zombie()
{
}
bool Zombie::init()
{
	std::string id = "Zombie";
	m_nHitPoint = MainLua::getInstance()->getIntegerFromTable(id,"hp");
	m_nDefense = MainLua::getInstance()->getIntegerFromTable(id,"defense");
	m_fSpeed = MainLua::getInstance()->getDoubleFromTable(id,"speed");

	bindSprite(Sprite::createWithSpriteFrameName("ZombieWalk1.png"));
	//初始化头部
	Size zombieSize = this->getContentSize();
	m_pHead = Sprite::createWithSpriteFrameName("ZombieHead1.png");//this->getSprite()->clone();
	m_pHead->setPosition(Point(zombieSize.width/2,0));
	m_pHead->setVisible(false);
	this->addChild(m_pHead);
	//初始化血条
	m_pHpBar = HpBar::create("Resources/HpBar.png","Resources/HpBarBG.png",m_nHitPoint);
	this->addChild(m_pHpBar);
	//设置位置
	Size size = m_pHpBar->getContentSize();
	m_pHpBar->setPosition(zombieSize.width/2 - size.width/2,0);
	return true;
}
void Zombie::hurt(int damage)
{
	int hp = m_nHitPoint - damage;
	
	//僵尸在半死亡状态下，受到攻击并不减少血量
	if(m_status == ZombieStatus::kZombieStatus_DeadAttack
		|| m_status == ZombieStatus::kZombieStatus_DeadWalk)
		return;
	setHitPoint(hp);

	m_pHpBar->setValue(hp);
	onHurt();
}
void Zombie::onHurt()
{
}
void Zombie::dead()
{
	onDead();
}
void Zombie::onDead()
{
}
void Zombie::attack(Plant*plant,float dt)
{
	m_fSkillTime += dt;
	if(m_fSkillTime >= 1.f)
	{
		m_fSkillTime = 0.f;
		plant->hurt(100);
	}
}
bool Zombie::changeState(ZombieStatus status)
{
	if(m_status == status)
		return false;
	m_status = status;
	return true;
}
bool Zombie::runIdleAction()
{
	if(changeState(ZombieStatus::kZombieStatus_Idle))
	{
		this->getSprite()->stopAllActions();
		this->getSprite()->runAction(onIdleAction());
		return true;
	}
	return false;
}
bool Zombie::runWalkAction()
{
	if(changeState(ZombieStatus::kZombieStatus_Walk))
	{
		this->getSprite()->stopAllActions();
		this->getSprite()->runAction(onWalkAction());
		return true;
	}
	return false;
}
bool Zombie::runAttackAction()
{
	if(changeState(ZombieStatus::kZombieStatus_Attack))
	{
		this->getSprite()->stopAllActions();
		this->getSprite()->runAction(onAttackAction());
		return true;
	}
	return false;
}
bool Zombie::runLostHeadAction()
{
	if(changeState(ZombieStatus::kZombieStatus_DeadWalk))
	{
		this->getSprite()->stopAllActions();
		this->getSprite()->runAction(onLostHeadAction());
		//头部动画
		m_pHead->setVisible(true);
		m_pHead->runAction(onHeadAction());
		return true;
	}
	return false;
}
bool Zombie::runLostAttackAction()
{
	if(changeState(ZombieStatus::kZombieStatus_DeadAttack))
	{
		this->getSprite()->stopAllActions();
		this->getSprite()->runAction(onLostAttackAction());
		//头部动画
		m_pHead->setVisible(true);
		m_pHead->runAction(onHeadAction());
		return true;
	}
	return false;
}
bool Zombie::runEntireDeadAction()
{
	if(changeState(ZombieStatus::kZombieStatus_EntireDead))
	{
		this->getSprite()->stopAllActions();
		this->getSprite()->runAction(onEntireDeadAction());
		return true;
	}
	return false;
}
bool Zombie::runDeadBombAction()
{
	if(changeState(ZombieStatus::kZombieStatus_DeadBomb))
	{
		this->getSprite()->stopAllActions();
		this->getSprite()->runAction(onDeadBombAction());
		return true;
	}
	return false;
}
FiniteTimeAction*Zombie::onIdleAction()
{
	return Entity::createAnimation("ZombieIdle%d.png",1,11,0.15f,-1);
}
FiniteTimeAction*Zombie::onWalkAction()
{
	return Entity::createAnimation("ZombieWalk%d.png",1,31,0.1f,-1);
}
FiniteTimeAction*Zombie::onAttackAction()
{
	return Entity::createAnimation("ZombieAttack%d.png",1,21,0.1f,-1);
}
FiniteTimeAction*Zombie::onLostAttackAction()
{
	return Entity::createAnimation("ZombieLostHeadAttack%d.png",1,11,0.1f,-1);
}
FiniteTimeAction*Zombie::onLostHeadAction()
{
	return Entity::createAnimation("ZombieLostHead%d.png",1,18,0.18f,-1);
}
FiniteTimeAction*Zombie::onEntireDeadAction()
{
	return Entity::createAnimation("ZombieDie%d.png",1,10,0.11f,1);
}
FiniteTimeAction*Zombie::onHeadAction()
{
	return Entity::createAnimation("ZombieHead%d.png",1,12,0.05f,1);
}
FiniteTimeAction*Zombie::onDeadBombAction()
{
	return Entity::createAnimation("BoomDie%d.png",1,20,0.2,1);
}