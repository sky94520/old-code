#include "PoleVaultingZombie.h"
#include "Plant.h"
#include "MoveBehavior.h"
#include "PlantLayer.h"
#include "Garnishry.h"

PoleVaultingZombie::PoleVaultingZombie()
	:m_bLosePole(false),m_state(State::None)
	,m_oldState(State::None)
	,m_duration(0.f),m_elapsed(0.f)
	,m_bIsActiveForBullet(true)
{
}

PoleVaultingZombie::~PoleVaultingZombie()
{
}

PoleVaultingZombie*PoleVaultingZombie::create(const string&zombieName)
{
	auto zombie = new PoleVaultingZombie();

	if (zombie && zombie->init(zombieName))
		zombie->autorelease();
	else
		SDL_SAFE_DELETE(zombie);

	return zombie;
}

bool PoleVaultingZombie::init(const string&zombieName)
{
	this->setZombieName(zombieName);

	//��ȡ����״̬��ͼ
	auto animationName = zombieName;
	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	//������ͼ
	auto firstFrame = animation->getFrames().front()->getSpriteFrame();

	m_pSprite = Sprite::createWithSpriteFrame(firstFrame);

	auto size = m_pSprite->getContentSize();
	//��λ�ý�����Ӧ�ĵ���
	m_pSprite->setPosition(size.width/2,size.height*0.55f);

	this->setContentSize(size);
	this->addChild(m_pSprite);
	//���ж���
	auto animate = Animate::create(animation);
	Speed*speed = Speed::create(animate,1.f);
	speed->setTag(ANIMATION_TAG);

	m_pSprite->runAction(speed);
	//����Ϊ����״̬
	m_state = m_oldState= State::Walk;

	return true;
}

void PoleVaultingZombie::updateAlive(float dt)
{
	//��������״̬
	if (m_state == State::Jump)
	{
		m_elapsed += dt;
		//������� ����Ƿ���ײ���Ƿ��Ǹ߼��
		if (m_elapsed >= m_duration)
		{
			m_elapsed = 0.f;
			this->jump2();
		}
	}//����2
	else if (m_state == State::Jump2)
	{
		m_elapsed += dt;
		//ת����������
		if (m_elapsed >= m_duration)
		{
			m_elapsed = 0.f;
			this->jumpEnd();
		}
	}
	else if (m_state == State::Walk)
	{
		//����Ŀ��
		if (m_pAim != nullptr)
		{
			if (m_bLosePole)
				this->changeState(State::Attack);
			else
				this->jump();
		}
	}
	else if (m_state == State::Attack)
	{
		//����Ŀ��
		if (m_pAim != nullptr)
		{
			this->eatAim(dt);
		}
		else
		{
			this->clearAim();
			this->changeState(State::Walk);
		}
	}
}

bool PoleVaultingZombie::isCanMove()const
{
	if (m_state == State::Walk || m_state == State::WalkDead)
		return true;

	return false;
}

float PoleVaultingZombie::getCurSpeed()const
{
	auto speed = ZombieBase::getCurSpeed();

	if (m_bLosePole)
		speed /= 3.f;

	return speed;
}

Rect PoleVaultingZombie::getCollisionBoundingBox()const
{
	auto rect = Character::getCollisionBoundingBox();

	if (!m_bLosePole)
	{
		rect.origin.x += rect.size.width/2.f;
		rect.origin.y += rect.size.height/2.f;
		rect.size.width /= 3 * 2;
		rect.size.height /= 2;
	}
	else
	{
		rect = ZombieBase::getCollisionBoundingBox();
	}

	return rect;
}

void PoleVaultingZombie::onNormalDead()
{
	if (m_state == State::Walk)
		changeState(State::WalkDead);
	else if (m_state == State::Attack)
		changeState(State::AttackDead);
}

void PoleVaultingZombie::onCRPDead()
{
	this->setDead(true);

	bool flipX = this->getSprite()->isFlipX();
	//��ʾ��������
	m_pDelegate->showZombieDie(this->getZombieName(),this->getPosition(),this->getTag(),flipX);
}

bool PoleVaultingZombie::isActiveForBullet()const
{
	return m_bIsActiveForBullet;
}

void PoleVaultingZombie::onButterDebuffEnter(const Point&pos)
{
	this->getSprite()->stopActionByTag(ANIMATION_TAG);
	//��ӻ�����ЧTODO
	Point startPos = pos;

	if (m_bLosePole)
	{
		startPos.x += 20.f;
	}
	else
	{
	}

	m_pDelegate->addButterSplat(startPos,this->getLocalZOrder(),this->getUniqueID());
}

void PoleVaultingZombie::onButterDebuffExit()
{
	ZombieBase::onButterDebuffExit();
	//��ǰû��������ԭ����
	if (this->getHitPoint() > 0)
	{
		m_state = State::None;

		this->changeState(m_oldState);
	}
}

void PoleVaultingZombie::onIceDebuffExit()
{
	ZombieBase::onButterDebuffExit();
	//��ǰû��������ԭ����
	if (this->getHitPoint() > 0)
	{
		m_state = State::None;

		this->changeState(m_oldState);
	}
}

void PoleVaultingZombie::jump()
{
	this->changeState(State::Jump);
	//�����ӵ�����ײ
	m_bIsActiveForBullet = false;
	//��ǰ��Ʒ�Ա�������
	m_pGarnishry->setImmuneForIce(true);
}

void PoleVaultingZombie::jump2()
{
	this->changeState(State::Jump2);
	//ʧȥ�Ÿ�
	m_bLosePole = true;
	//�Ƿ�������ȥ TODO
	//ֱ������λ��
	auto pos = this->getPosition();
	auto size = this->getContentSize();
	auto rect = this->getCollisionBoundingBox();

	//��ȡ��ǰ��Ŀ���Ƿ���ֲ��͸߼��
	//����ʧ��
	if (m_pAim != nullptr 
		&& m_pAim->getCharacterType() == CharacterType::Plant
		&& PlantLayer::isTallNut(static_cast<Plant*>(m_pAim)))
	{
		this->setPosition(pos - Point(40.f,0.f));
	}
	else
	{
		this->setPosition(pos - Point(120.f,0.f));
	}
	//�����ǰĿ��
	this->clearAim();
}

void PoleVaultingZombie::jumpEnd()
{
	this->changeState(State::Walk);
	m_bIsActiveForBullet = true;
	//���Ա�������
	m_pGarnishry->setImmuneForIce(false);

	this->clearAim();
}

void PoleVaultingZombie::changeState(State state)
{
	//״̬û�з����ı䣬ֱ���˳�
	if (m_state == state)
		return ;
	//������jump��jump2��״̬
	if (m_state != State::Jump || m_state != State::Jump2)
		m_oldState = state;
	m_state = state;

	string animationName;
	Animation*animation = nullptr;
	auto zombieName = this->getZombieName();

	if (m_state == State::Walk)
	{
		if (m_bLosePole)
		{
			animationName = StringUtils::format("%sWalk",zombieName.c_str());
		}
		else
		{
			animationName = zombieName;
		}

		animation = AnimationCache::getInstance()->getAnimation(animationName);
	}
	else if (m_state == State::Attack)
	{
		animationName = StringUtils::format("%sAttack",zombieName.c_str());
		animation = AnimationCache::getInstance()->getAnimation(animationName);
	}
	else if (m_state == State::Jump)
	{
		animationName = StringUtils::format("%sJump",zombieName.c_str());
		animation = AnimationCache::getInstance()->getAnimation(animationName);
		m_duration = animation->getDuration();
	}
	else if (m_state == State::Jump2)
	{
		animationName = StringUtils::format("%sJump2",zombieName.c_str());
		animation = AnimationCache::getInstance()->getAnimation(animationName);
		m_duration = animation->getDuration();
	}
	else if (m_state == State::WalkDead)
	{
		if (!m_bLosePole)
		{
			animationName = StringUtils::format("%sLostHead",zombieName.c_str());
		}
		else
		{
			animationName = StringUtils::format("%sLostHeadWalk",zombieName.c_str());
		}
		animation = AnimationCache::getInstance()->getAnimation(animationName);
		this->showZombieHead();
	}
	else if (m_state == State::AttackDead)
	{
		animationName = StringUtils::format("%sLostHeadAttack",zombieName.c_str());
		animation = AnimationCache::getInstance()->getAnimation(animationName);

		this->showZombieHead();
	}

	if (animation != nullptr)
		ZombieBase::changeAnimation(animation);
}

void PoleVaultingZombie::showZombieHead()
{
	//����λ��
	Point bornPos = this->getPosition();
	Size size = this->getContentSize();

	m_pDelegate->showZombieHead(this->getZombieName(),bornPos,this->getTag(),false);
}