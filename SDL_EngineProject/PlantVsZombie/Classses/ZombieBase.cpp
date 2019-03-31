#include "ZombieBase.h"
#include "Plant.h"
#include "MoveBehavior.h"
#include "Terrain.h"
#include "HpBar.h"
#include "Garnishry.h"

ZombieBase::ZombieBase()
	:m_fBaseSpeed(0.f),m_nRow(0)
	,m_pMoveBehavior(nullptr)
	,m_fColdDownTime(0.f),m_nDamage(0)
	,m_pDelegate(nullptr),m_fCriticalPoint(0.f)
	,m_pHpBar(nullptr),m_eatingElapsed(0.f)
	,_isDying(false),m_bConfused(false)
{
	this->setCharacterType(CharacterType::Zombie);
}

ZombieBase::~ZombieBase()
{
	SDL_SAFE_DELETE(m_pMoveBehavior);
}

void ZombieBase::setDelegate(ZombieDelegate*pDelegate)
{
	m_pDelegate = pDelegate;
}

void ZombieBase::setRow(int row)
{
	m_nRow = row;
}

void ZombieBase::setAim(Character*character)
{	
	m_pAim = character;
}

Character*ZombieBase::getAim()
{
	return m_pAim;
}

void ZombieBase::clearAim()
{
	m_pAim = nullptr;
	//重新计时
	m_eatingElapsed = 0.f;
}

void ZombieBase::eatAim(float dt)
{
	m_eatingElapsed += dt;

	if (m_eatingElapsed >= this->getColdDownTime())
	{
		m_eatingElapsed -= this->getColdDownTime();
		//攻击目标
		m_pAim->hurt(this->getDamage(),AttackType::Common);
		//如果目标是植物，则调用对应的方法
		if (m_pAim->getCharacterType() == CharacterType::Plant)
		{
			static_cast<Plant*>(m_pAim)->eatenByZombie(this);
		}
	}
}

void ZombieBase::addGarnishry(Garnishry*garnishry)
{
	m_pGarnishry = garnishry;

	this->addChild(m_pGarnishry);
}

Garnishry*ZombieBase::getGarnishry()
{
	return m_pGarnishry;
}

bool ZombieBase::isDying()const
{
	bool bRet = this->getCriticalPoint() <= 0;

	return Character::isDying() && bRet;
}

void ZombieBase::setVertexBox(const Rect&rect)
{
	m_vertexBox = rect;
}

Rect ZombieBase::getVertexBox()const
{
	return m_vertexBox;
}

Rect ZombieBase::getCollisionBoundingBox()const
{
	auto pos = this->getBoundingBox().origin;

	return Rect(pos + m_vertexBox.origin,m_vertexBox.size);
}

void ZombieBase::hurt(int baseDamage,AttackType attackType)
{
	int afterDamage = baseDamage;
	bool bShowHurt = true;
	//调用饰品，吸收伤害
	if (m_pGarnishry != nullptr && m_pGarnishry->getHitPoint() > 0)
	{
		afterDamage = m_pGarnishry->absorbDamage(baseDamage,attackType);

		//如果饰品死亡，回调饰品死亡函数
		if (m_pGarnishry->getHitPoint() <= 0)
			onGarnishryDead();
	}
	//当前不会受伤，直接返回
	if (afterDamage < 0)
		return ;
	//尝试消除减速debuff
	if (attackType == AttackType::FireAndKillDeceleration)
	{
		this->removeDebuff(DebuffType::Deceleration);
	}
	//受伤动画
	this->showHurtAction();

	auto afterHP = this->getHitPoint() - afterDamage;
	bool bDead = false;

	if (afterHP <= 0)
	{
		afterHP = 0;
		bDead = true;
	}
	this->setHitPoint(afterHP);
	//设置血量条
	if (m_pHpBar != nullptr)
	{
		m_pHpBar->setValue((float)afterHP);
	}
	onHurt();
	//回调死亡函数 保证只是回调一次
	if (bDead && ! _isDying)
	{
		_isDying = true;

		if (attackType == AttackType::Swallow)
		{
			onSwallowDead();
		}
		else if (attackType == AttackType::Boom)
		{
			onBoomDead();
		}
		else
		{
			onNormalDead();
		}
		//移除所有的dubuff
		this->removeAllDebuff();
	}
}

void ZombieBase::deceleration(AttackType type,float duration)
{
	//当前僵尸死亡
	if (this->getHitPoint() <= 0)
	{
		return;
	}
	//当前饰品可用，并且对当前的类型免疫
	if (m_pGarnishry != nullptr && m_pGarnishry->getHitPoint() > 0
		&& m_pGarnishry->isImmuneForDeceleration(type))
	{
		return ;
	}
	//调用对应的方法
	Debuff debuff(DebuffType::Deceleration,duration);

	auto callback = SDL_CALLBACK_0(ZombieBase::onDecelerationDebuffEnter,this);

	this->addDebuff(debuff,callback);
}

void ZombieBase::butter(const Point&pos,float duration)
{
	//当前僵尸死亡
	if (this->getHitPoint() <= 0)
	{
		return;
	}
	//当前饰品可用，并且对当前的类型免疫
	if (m_pGarnishry != nullptr && m_pGarnishry->getHitPoint() > 0
		&& m_pGarnishry->isImmuneForButter())
	{
		return ;
	}
	Debuff debuff(DebuffType::Butter,duration);

	auto callback = SDL_CALLBACK_0(ZombieBase::onButterDebuffEnter,this,pos);
	this->addDebuff(debuff,callback);
}

void ZombieBase::ice(float duration)
{
	//当前僵尸死亡
	if (this->getHitPoint() <= 0)
	{
		return;
	}
	//当前饰品可用，并且对当前的类型免疫
	if (m_pGarnishry != nullptr && m_pGarnishry->getHitPoint() > 0
		&& m_pGarnishry->isImmuneForIce())
	{
		return ;
	}
	Debuff debuff(DebuffType::Ice,duration);
	auto callback = SDL_CALLBACK_0(ZombieBase::onIceDebuffEnter,this);

	this->addDebuff(debuff,callback);
}

void ZombieBase::setMoveBehavior(MoveBehavior*behavior)
{
	SDL_SAFE_DELETE(m_pMoveBehavior);

	m_pMoveBehavior = behavior;
}

MoveBehavior*ZombieBase::getMoveBehavior()
{
	return m_pMoveBehavior;
}

void ZombieBase::bindHpBar(HpBar*hpBar)
{
	m_pHpBar = hpBar;

	this->addChild(m_pHpBar);
}

bool ZombieBase::isDuringDebuff(DebuffType debuffType)const
{
	auto it = find_if(m_debuffs.begin(),m_debuffs.end(),[debuffType](Debuff debuff)
	{
		return debuff.type == debuffType;
	});
	//存在该debuff并且持续时间大于0时，才有效
	if (it != m_debuffs.end() && it->duration > 0.f)
	{
		return true;
	}
	return false;
}

bool ZombieBase::isDuringDeceleration()const
{
	return this->isDuringDebuff(DebuffType::Deceleration);
}

bool ZombieBase::isDuringButter()const
{
	return this->isDuringDebuff(DebuffType::Butter);
}

bool ZombieBase::isDuringIce()const
{
	return this->isDuringDebuff(DebuffType::Ice);
}

bool ZombieBase::isPausedLogic()const
{
	return this->isDuringButter() 
		|| this->isDuringIce();
}

int ZombieBase::getRow()const
{
	return m_nRow;
}

float ZombieBase::getCurSpeed()const
{
	auto speed = m_fBaseSpeed;
	//减速成三分之二
	if (this->isDuringDeceleration())
	{
		speed = speed /3.f * 2.f;
	}
	return speed;
}

void ZombieBase::update(float dt)
{
	//当前僵尸血量小于0，死亡
	if (this->getHitPoint() <= 0)
	{
		auto afterCRP = this->getCriticalPoint() - 0.4f;
		this->setCriticalPoint(afterCRP);
		//僵尸真正死亡
		if (afterCRP <= 0.f)
		{
			onCRPDead();
		}
	}
	//在定住时暂时不更新内部逻辑
	else if (!this->isPausedLogic())
	{
		updateAlive(dt);
	}
	//进行debuff的更新
	this->updateDebuff(dt);
	//当前可以运动
	if (!this->isPausedLogic() && m_pMoveBehavior != nullptr
		&& isCanMove())
	{
		m_pMoveBehavior->performMove(this);
	}
}

bool ZombieBase::isCanMove()const
{
	return true;
}

void ZombieBase::onHurt()
{
}

void ZombieBase::onNormalDead()
{
	this->setDead(true);
}

void ZombieBase::onCRPDead()
{
	this->setDead(true);
	//显示死亡动画
	bool flipX = this->getSprite()->isFlipX();
	auto pos = this->getPosition();
	auto size = this->getContentSize();

	if (flipX)
		pos.x += size.width/4;

	m_pDelegate->showZombieDie(this->getZombieName(),pos,this->getTag(),flipX);
}

void ZombieBase::onSwallowDead()
{
	this->setDead(true);
}

void ZombieBase::onBoomDead()
{
	this->setDead(true);
	bool flipX = this->getSprite()->isFlipX();

	m_pDelegate->showZombieBoom(this->getZombieName(),this->getPosition(),this->getTag(),flipX);
}

void ZombieBase::onGarnishryDead()
{
}

void ZombieBase::onDecelerationDebuffEnter()
{
	if (m_pSprite)
	{
		m_pSprite->setColorMod(Color3B(0,255,255));
		
		auto action = this->getSprite()->getActionByTag(ANIMATION_TAG);
		auto speed = dynamic_cast<Speed*>(action);
		//存在该Speed才设置
		if (speed != nullptr)
			speed->setSpeed(0.7f);
	}
}

void ZombieBase::onDecelerationDebuffExit()
{
	if (m_pSprite)
	{
		m_pSprite->setColorMod(Color3B(255,255,255));

		auto action = this->getSprite()->getActionByTag(ANIMATION_TAG);
		auto speed = dynamic_cast<Speed*>(action);

		if (speed != nullptr)
			speed->setSpeed(1.f);
	}
}

void ZombieBase::onButterDebuffEnter(const Point&pos)
{
	//暂停精灵所有动作
	this->getSprite()->stopActionByTag(ANIMATION_TAG);
	//添加黄油特效
	m_pDelegate->addButterSplat(pos,this->getLocalZOrder(),this->getUniqueID());
}

void ZombieBase::onButterDebuffExit()
{
	m_pDelegate->removeButterSplat(this->getUniqueID());
}

void ZombieBase::onIceDebuffEnter()
{
	this->getSprite()->stopActionByTag(ANIMATION_TAG);
	//添加冰冻特效

	Rect rect = this->getCollisionBoundingBox();

	Point pos = Point(rect.origin.x + rect.size.width/2,rect.origin.y + rect.size.height);

	m_pDelegate->addIceTrap(pos,this->getLocalZOrder(),this->getUniqueID());
}

void ZombieBase::onIceDebuffExit()
{
	m_pDelegate->removeIceTrap(this->getUniqueID());
}

bool ZombieBase::isActiveForBullet()const
{
	return true;
}

void ZombieBase::setSpriteFlipX(bool flipX)
{
	Point pos;

	if (flipX)
	{
		auto rect = this->getVertexBox();

		pos = Point(rect.origin.x + rect.size.width/2,this->getSprite()->getPositionY());
	}
	else
	{
		auto size = this->getContentSize();
		pos = Point(size.width/2,size.height/2);
	}

	this->getSprite()->setPosition(pos);
	this->getSprite()->setFlipX(flipX);
}

void ZombieBase::showHurtAction()
{
	const int tag = 5;
	auto sprite = this->getSprite();
	//获取一开始的颜色
	Color3B oldColor;

	if (this->isDuringDeceleration())
		oldColor = Color3B(0,128,0xff);
	else if (this->getSprite()->isFlipX())
		oldColor = Color3B(0,0,0xff);
	else
		oldColor = Color3B(255,255,255);
	//使僵尸的身体变白
	sprite->setColorMod(Color3B(215,215,215));
	//在一定时间后还原
	DelayTime*delayTime = DelayTime::create(0.15f);
	CallFunc*end = CallFunc::create([sprite,oldColor]()
	{
		sprite->setColorMod(oldColor);
	});

	auto seq = Sequence::createWithTwoActions(delayTime,end);
	seq->setTag(tag);
	//先停止原先动画
	sprite->stopActionByTag(tag);

	sprite->runAction(seq);
}

void ZombieBase::removeDebuff(DebuffType debuffType)
{
	auto it = find_if(m_debuffs.begin(),m_debuffs.end(),[debuffType](Debuff debuff)
	{
		return debuff.type == debuffType && debuff.duration > 0.f;
	});
	//找到该debuff,并且移除
	if (it != m_debuffs.end())
	{
		this->removeDebuff(it);
	}
}

vector<Debuff>::iterator ZombieBase::removeDebuff(vector<Debuff>::iterator it)
{
	auto &debuff = *it;
	auto type = debuff.type;
	it = m_debuffs.erase(it);

	//debuff结束
	if (type == DebuffType::Deceleration)
	{
		this->onDecelerationDebuffExit();
	}
	else if (type == DebuffType::Butter)
	{
		this->onButterDebuffExit();
	}
	else if (type == DebuffType::Ice)
	{
		this->onIceDebuffExit();
	}
	return it;
}

void ZombieBase::removeAllDebuff()
{
	//进行debuff的遍历
	for (auto it = m_debuffs.begin();it != m_debuffs.end();)
	{
		it = this->removeDebuff(it);
	}
}

void  ZombieBase::addDebuff(Debuff d,const function<void ()> &callback)
{
	//目前已经存在该debuff
	auto it = find_if(m_debuffs.begin(),m_debuffs.end(),[d](Debuff debuff)
	{
		return debuff.type == d.type;
	});

	if (it != m_debuffs.end())
	{
		it->duration = d.duration;
	}
	else//添加buff
	{
		m_debuffs.push_back(Debuff(d.type,d.duration));
		//回调对应的函数
		callback();
	}
}

void ZombieBase::updateDebuff(float dt)
{
	//进行debuff的更新
	for (auto it = m_debuffs.begin();it != m_debuffs.end();)
	{
		auto &debuff = *it;

		debuff.duration -= dt;
		//debuff结束
		if (debuff.duration <= 0.f)
		{
			if (debuff.type == DebuffType::Deceleration)
			{
				it = m_debuffs.erase(it);
				this->onDecelerationDebuffExit();
			}
			else if (debuff.type == DebuffType::Butter)
			{
				it = m_debuffs.erase(it);
				this->onButterDebuffExit();
			}
			else if (debuff.type == DebuffType::Ice)
			{
				it = m_debuffs.erase(it);
				this->onIceDebuffExit();
			}
		}
		else
		{
			it++;
		}
	}
}

void ZombieBase::changeAnimation(Animation*animation)
{
	//停止原先的动画
	this->getSprite()->stopActionByTag(ANIMATION_TAG);
	//切换当前贴图
	this->getSprite()->setSpriteFrame(animation->getFrames().front()->getSpriteFrame());

	//当前逻辑正在更新，或者已经死亡，则运行动画
	if (!this->isPausedLogic() || this->getHitPoint() <= 0)
	{
		auto animate = Animate::create(animation);
		//是否处于减速状态
		Speed*speed = Speed::create(animate,1.f);
		if (this->isDuringDeceleration())
			speed->setSpeed(0.7f);

		speed->setTag(ANIMATION_TAG);

		this->getSprite()->runAction(speed);
	}
}