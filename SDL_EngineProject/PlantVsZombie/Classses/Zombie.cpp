#include "Zombie.h"
#include "Plant.h"
#include "MoveBehavior.h"

Zombie::Zombie()
	:m_state(State::None),m_nType(1)
	,m_oldState(State::None)
{
}

Zombie::~Zombie()
{
}

Zombie*Zombie::create(const string&zombieName)
{
	auto zombie = new Zombie();

	if (zombie && zombie->init(zombieName))
		zombie->autorelease();
	else
		SDL_SAFE_DELETE(zombie);

	return zombie;
}

bool Zombie::init(const string&zombieName)
{
	this->setZombieName(zombieName);
	//��������todo
	m_nType = 1;
	//��ȡ����״̬��ͼ
	auto animationName = StringUtils::format("%sWalk%02d",m_zombieName.c_str(),m_nType);
	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	//������ͼ
	auto firstFrame = animation->getFrames().front()->getSpriteFrame();
	this->bindSpriteWithSpriteFrame(firstFrame);
	//���ж���
	auto animate = Animate::create(animation);
	Speed*speed = Speed::create(animate,1.f);
	speed->setTag(ANIMATION_TAG);

	m_pSprite->runAction(speed);
	//����Ϊ����״̬
	m_state = State::Walk;

	return true;
}

void Zombie::updateAlive(float dt)
{
	if (m_state == State::Idle)
		return;
	//��ǰ���ڹ���Ŀ��
	if (m_pAim != nullptr)
	{
		this->changeState(State::Attack);
		
		this->eatAim(dt);
	}
	else//�����ڹ���Ŀ�������¼�ʱ ��������
	{
		this->clearAim();
		this->changeState(State::Walk);
	}
}

bool Zombie::isCanMove()const
{
	if (m_state == State::Walk || m_state == State::WalkDead)
	{
		return true;
	}
	return false;
}

void Zombie::onNormalDead()
{
	if (m_state == State::Walk)
		changeState(State::WalkDead);
	else if (m_state == State::Attack)
		changeState(State::AttackDead);
}

void Zombie::changeState(State state)
{
	//״̬û�з����ı䣬ֱ���˳�
	if (m_state == state)
		return ;
	m_oldState = m_state;
	m_state = state;
	string animationName;

	if (m_state == State::Walk)
	{
		animationName = StringUtils::format("%sWalk%02d",m_zombieName.c_str(),m_nType);
	}
	else if (m_state == State::Attack)
	{
		animationName = StringUtils::format("%sAttack",m_zombieName.c_str());
	}
	else if (m_state == State::WalkDead)
	{
		animationName = "ZombieLostHead";

		this->showZombieHead();
	}
	else if (m_state == State::AttackDead)
	{
		animationName = "ZombieLostHeadAttack";
		
		this->showZombieHead();
	}
	if (animationName.empty())
	{
		return ;
	}

	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	ZombieBase::changeAnimation(animation);
}

void Zombie::showZombieHead()
{
	//����λ��
	Point bornPos = this->getPosition();
	Size size = this->getContentSize();

	bornPos.x += size.width/4.f;

	m_pDelegate->showZombieHead(this->getZombieName(),bornPos,this->getTag(),false);
}

void Zombie::onButterDebuffEnter(const Point&pos)
{
	this->getSprite()->stopActionByTag(ANIMATION_TAG);
	//��ӻ�����ЧTODO
	m_pDelegate->addButterSplat(pos + Point(0,20.f),this->getLocalZOrder(),this->getUniqueID());
}

void Zombie::onButterDebuffExit()
{
	ZombieBase::onButterDebuffExit();
	//��ǰû��������ԭ����
	if (this->getHitPoint() > 0)
	{
		m_state = State::None;

		this->changeState(m_oldState);
	}
}

void Zombie::onIceDebuffExit()
{
	ZombieBase::onButterDebuffExit();
	//��ǰû��������ԭ����
	if (this->getHitPoint() > 0)
	{
		m_state = State::None;

		this->changeState(m_oldState);
	}
}