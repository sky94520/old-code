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
	//���¼�ʱ
	m_eatingElapsed = 0.f;
}

void ZombieBase::eatAim(float dt)
{
	m_eatingElapsed += dt;

	if (m_eatingElapsed >= this->getColdDownTime())
	{
		m_eatingElapsed -= this->getColdDownTime();
		//����Ŀ��
		m_pAim->hurt(this->getDamage(),AttackType::Common);
		//���Ŀ����ֲ�����ö�Ӧ�ķ���
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
	//������Ʒ�������˺�
	if (m_pGarnishry != nullptr && m_pGarnishry->getHitPoint() > 0)
	{
		afterDamage = m_pGarnishry->absorbDamage(baseDamage,attackType);

		//�����Ʒ�������ص���Ʒ��������
		if (m_pGarnishry->getHitPoint() <= 0)
			onGarnishryDead();
	}
	//��ǰ�������ˣ�ֱ�ӷ���
	if (afterDamage < 0)
		return ;
	//������������debuff
	if (attackType == AttackType::FireAndKillDeceleration)
	{
		this->removeDebuff(DebuffType::Deceleration);
	}
	//���˶���
	this->showHurtAction();

	auto afterHP = this->getHitPoint() - afterDamage;
	bool bDead = false;

	if (afterHP <= 0)
	{
		afterHP = 0;
		bDead = true;
	}
	this->setHitPoint(afterHP);
	//����Ѫ����
	if (m_pHpBar != nullptr)
	{
		m_pHpBar->setValue((float)afterHP);
	}
	onHurt();
	//�ص��������� ��ֻ֤�ǻص�һ��
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
		//�Ƴ����е�dubuff
		this->removeAllDebuff();
	}
}

void ZombieBase::deceleration(AttackType type,float duration)
{
	//��ǰ��ʬ����
	if (this->getHitPoint() <= 0)
	{
		return;
	}
	//��ǰ��Ʒ���ã����ҶԵ�ǰ����������
	if (m_pGarnishry != nullptr && m_pGarnishry->getHitPoint() > 0
		&& m_pGarnishry->isImmuneForDeceleration(type))
	{
		return ;
	}
	//���ö�Ӧ�ķ���
	Debuff debuff(DebuffType::Deceleration,duration);

	auto callback = SDL_CALLBACK_0(ZombieBase::onDecelerationDebuffEnter,this);

	this->addDebuff(debuff,callback);
}

void ZombieBase::butter(const Point&pos,float duration)
{
	//��ǰ��ʬ����
	if (this->getHitPoint() <= 0)
	{
		return;
	}
	//��ǰ��Ʒ���ã����ҶԵ�ǰ����������
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
	//��ǰ��ʬ����
	if (this->getHitPoint() <= 0)
	{
		return;
	}
	//��ǰ��Ʒ���ã����ҶԵ�ǰ����������
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
	//���ڸ�debuff���ҳ���ʱ�����0ʱ������Ч
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
	//���ٳ�����֮��
	if (this->isDuringDeceleration())
	{
		speed = speed /3.f * 2.f;
	}
	return speed;
}

void ZombieBase::update(float dt)
{
	//��ǰ��ʬѪ��С��0������
	if (this->getHitPoint() <= 0)
	{
		auto afterCRP = this->getCriticalPoint() - 0.4f;
		this->setCriticalPoint(afterCRP);
		//��ʬ��������
		if (afterCRP <= 0.f)
		{
			onCRPDead();
		}
	}
	//�ڶ�סʱ��ʱ�������ڲ��߼�
	else if (!this->isPausedLogic())
	{
		updateAlive(dt);
	}
	//����debuff�ĸ���
	this->updateDebuff(dt);
	//��ǰ�����˶�
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
	//��ʾ��������
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
		//���ڸ�Speed������
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
	//��ͣ�������ж���
	this->getSprite()->stopActionByTag(ANIMATION_TAG);
	//��ӻ�����Ч
	m_pDelegate->addButterSplat(pos,this->getLocalZOrder(),this->getUniqueID());
}

void ZombieBase::onButterDebuffExit()
{
	m_pDelegate->removeButterSplat(this->getUniqueID());
}

void ZombieBase::onIceDebuffEnter()
{
	this->getSprite()->stopActionByTag(ANIMATION_TAG);
	//��ӱ�����Ч

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
	//��ȡһ��ʼ����ɫ
	Color3B oldColor;

	if (this->isDuringDeceleration())
		oldColor = Color3B(0,128,0xff);
	else if (this->getSprite()->isFlipX())
		oldColor = Color3B(0,0,0xff);
	else
		oldColor = Color3B(255,255,255);
	//ʹ��ʬ��������
	sprite->setColorMod(Color3B(215,215,215));
	//��һ��ʱ���ԭ
	DelayTime*delayTime = DelayTime::create(0.15f);
	CallFunc*end = CallFunc::create([sprite,oldColor]()
	{
		sprite->setColorMod(oldColor);
	});

	auto seq = Sequence::createWithTwoActions(delayTime,end);
	seq->setTag(tag);
	//��ֹͣԭ�ȶ���
	sprite->stopActionByTag(tag);

	sprite->runAction(seq);
}

void ZombieBase::removeDebuff(DebuffType debuffType)
{
	auto it = find_if(m_debuffs.begin(),m_debuffs.end(),[debuffType](Debuff debuff)
	{
		return debuff.type == debuffType && debuff.duration > 0.f;
	});
	//�ҵ���debuff,�����Ƴ�
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

	//debuff����
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
	//����debuff�ı���
	for (auto it = m_debuffs.begin();it != m_debuffs.end();)
	{
		it = this->removeDebuff(it);
	}
}

void  ZombieBase::addDebuff(Debuff d,const function<void ()> &callback)
{
	//Ŀǰ�Ѿ����ڸ�debuff
	auto it = find_if(m_debuffs.begin(),m_debuffs.end(),[d](Debuff debuff)
	{
		return debuff.type == d.type;
	});

	if (it != m_debuffs.end())
	{
		it->duration = d.duration;
	}
	else//���buff
	{
		m_debuffs.push_back(Debuff(d.type,d.duration));
		//�ص���Ӧ�ĺ���
		callback();
	}
}

void ZombieBase::updateDebuff(float dt)
{
	//����debuff�ĸ���
	for (auto it = m_debuffs.begin();it != m_debuffs.end();)
	{
		auto &debuff = *it;

		debuff.duration -= dt;
		//debuff����
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
	//ֹͣԭ�ȵĶ���
	this->getSprite()->stopActionByTag(ANIMATION_TAG);
	//�л���ǰ��ͼ
	this->getSprite()->setSpriteFrame(animation->getFrames().front()->getSpriteFrame());

	//��ǰ�߼����ڸ��£������Ѿ������������ж���
	if (!this->isPausedLogic() || this->getHitPoint() <= 0)
	{
		auto animate = Animate::create(animation);
		//�Ƿ��ڼ���״̬
		Speed*speed = Speed::create(animate,1.f);
		if (this->isDuringDeceleration())
			speed->setSpeed(0.7f);

		speed->setTag(ANIMATION_TAG);

		this->getSprite()->runAction(speed);
	}
}