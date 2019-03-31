#include "ConeheadZombie.h"
#include "Terrain.h"
#include "Plant.h"
#include "MoveBehavior.h"
#include "HpBar.h"

ConeheadZombie::ConeheadZombie()
	:m_pInnerZombie(nullptr),m_elapsed(0.f)
{
}

ConeheadZombie::~ConeheadZombie()
{
}

ConeheadZombie*ConeheadZombie::create(const string&zombieName,ZombieBase*zombieBase)
{
	auto zombie = new ConeheadZombie();

	if (zombie && zombie->init(zombieName,zombieBase))
		zombie->autoRelease();
	else
		SDL_SAFE_DELETE(zombie);

	return zombie;
}

bool ConeheadZombie::init(const string&zombieName,ZombieBase*zombieBase)
{
	//������ͼ
	this->setZombieName(zombieName);
	//��ȡվ��״̬��ͼ
	auto animationName = StringUtils::format("%sIdle",zombieName.c_str());
	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	//������ͼ
	auto firstFrame = animation->getFrames().front()->getSpriteFrame();

	m_pSprite = Sprite::createWithSpriteFrame(firstFrame);

	auto size = m_pSprite->getContentSize();

	m_pSprite->setPosition(size.width/2,size.height/2);

	this->setContentSize(size);
	this->addChild(m_pSprite);
	//����վ������
	auto animate = Animate::create(animation);
	animate->setTag(ANIMATION_TAG);

	m_pSprite->runAction(animate);
	//����Ϊվ��״̬
	m_state = State::Idle;
	//��ӽ�ʬ
	m_pInnerZombie = zombieBase;
	m_pInnerZombie->setPosition(size.width/2 + 10.f,size.height/2);
	//TODO ����΢����ʾ
	//m_pInnerZombie->setVisible(false);
	this->addChild(m_pInnerZombie);

	return true;
}

void ConeheadZombie::setDelegate(ZombieDelegate*pDelegate)
{
	ZombieBase::setDelegate(pDelegate);
	m_pInnerZombie->setDelegate(pDelegate);
}

void ConeheadZombie::setAim(Terrain*plant)
{
	ZombieBase::setAim(plant);
	m_pInnerZombie->setAim(plant);
}

void ConeheadZombie::setMoveBehavior(MoveBehavior*behavior)
{
	ZombieBase::setMoveBehavior(behavior);
	//m_pInnerZombie->setMoveBehavior(behavior);
}

bool ConeheadZombie::isDying()const
{
	return m_pInnerZombie->isDying();
}

bool ConeheadZombie::isDead()const
{
	return m_pInnerZombie->isDead();
}

void ConeheadZombie::update(float dt)
{
	//��ǰ·�ϻ�û����
	if (this->getHitPoint() > 0)
	{
		this->coneheadUpdate(dt);
	}
	//·���Ѿ�������������ڲ���ʬ���и���
	{
		m_pInnerZombie->update(dt);
	}
}

float ConeheadZombie::getCurSpeed()const
{
	float speed = m_fBaseSpeed;

	if (this->getHitPoint() <= 0)
		speed = m_pInnerZombie->getCurSpeed();

	return speed;
}

Rect ConeheadZombie::getCollisionBoundingBox()const
{
	Rect rect = this->getSprite()->getSpriteFrameRect();
	//����x y����ĸ���
	auto r = this->getBoundingBox();

	rect.origin.x += r.origin.x;
	rect.origin.y += r.origin.y;

	return rect;
}

int ConeheadZombie::hurtHook(int baseDamage,AttackType attackType)
{
	int damage;
	//·�ϻ�û���� TODO
	if (this->getHitPoint() > 0)
	{
		damage = baseDamage;
	}
	else
	{
		damage = 0;
		m_pInnerZombie->hurt(baseDamage,attackType);
		//m_pInnerZombie->hurtHook(baseDamage,attackType);
	}

	return damage;
}

void ConeheadZombie::onHurt()
{
	if (this->getHitPoint() > 0)
	{
		return;
	}
	else
	{
		m_pInnerZombie->onHurt();
	}
}

void ConeheadZombie::onDead()
{
	//·������
	//����ʾ��ǰ�Ľ�ʬ
	m_pSprite->setVisible(false);
	m_pHpBar->setVisible(false);
	//��ʾ�ڲ���ʬ
	m_pInnerZombie->setVisible(true);
}

void ConeheadZombie::changeState(State state)
{
	//״̬û�з����ı䣬ֱ���˳�
	if (m_state == state)
		return ;

	m_state = state;
	string animationName;

	if (m_state == State::Walk)
	{
		animationName = StringUtils::format("%sWalk",m_zombieName.c_str());
	}
	else if (m_state == State::Attack)
	{
		animationName = StringUtils::format("%sAttack",m_zombieName.c_str());
	}
	//ֹͣԭ�ȵĶ���
	this->getSprite()->stopActionByTag(ANIMATION_TAG);

	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	auto animate = Animate::create(animation);
	animate->setTag(ANIMATION_TAG);

	this->getSprite()->runAction(animate);
}

void ConeheadZombie::coneheadUpdate(float dt)
{
	//TODO ��ǰ�������վ��״̬����ֱ����ת������״̬
	if (m_state == State::Idle)
	{
		this->changeState(State::Walk);
	}
	//��ǰ���ڹ���Ŀ��
	else if (m_pAim != nullptr)
	{
		if (m_pAim->getInnerPlant() != nullptr)
		{
			this->changeState(State::Attack);
			m_elapsed += dt;
			//���﹥��ʱ��
			if (m_elapsed >= this->getColdDownTime())
			{
				m_elapsed -= this->getColdDownTime();
				//���й���
				auto topPlant = m_pDelegate->getTopPlant(m_pAim);
				topPlant->hurt(this->getDamage());
			}
		}
		else//���¼�ʱ
		{
			this->clearAim();
			m_elapsed = 0.f;
		}

	}
	//û�й���Ŀ�꣬����
	else if (m_pAim == nullptr)
	{
		this->changeState(State::Walk);
	}
	if (m_pMoveBehavior != nullptr &&
		m_state == State::Walk)
	{
		m_pMoveBehavior->performMove(this);
	}
}