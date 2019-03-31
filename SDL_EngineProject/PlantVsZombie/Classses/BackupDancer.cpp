#include "BackupDancer.h"

BackupDancer::BackupDancer()
	:m_state(State::None),m_duration(0.f)
	,m_elapsed(0.f)
{
}

BackupDancer::~BackupDancer()
{
}

BackupDancer*BackupDancer::create(const string& zombieName)
{
	auto zombie = new BackupDancer();

	if (zombie && zombie->init(zombieName))
		zombie->autorelease();
	else
		SDL_SAFE_DELETE(zombie);

	return zombie;
}

bool BackupDancer::init(const string& zombieName)
{
	this->setZombieName(zombieName);
	//��ȡվ��״̬��ͼ
	auto animationName = StringUtils::format("%sWalk",m_zombieName.c_str());
	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	//������ͼ
	auto firstFrame = animation->getFrames().front()->getSpriteFrame();

	this->bindSpriteWithSpriteFrame(firstFrame);
	//����վ������
	auto animate = Animate::create(animation);
	Speed*speed = Speed::create(animate,1.f);
	speed->setTag(ANIMATION_TAG);

	m_pSprite->runAction(speed);

	return true;
}

void BackupDancer::updateAlive(float dt)
{
	//�Զ�ת������״̬
	if (m_state == State::None)
	{
		this->changeState(State::Rising);
		//��������
		this->setOpenShade(true);
		//��ʾ������Ч
		auto pos = this->getPosition();
		Size size = this->getContentSize();
		auto localZOrder = this->getLocalZOrder();

		m_pDelegate->showRisingDirt(pos + Point(0,size.height/2),localZOrder + 1);
	}//����״̬
	if (m_state == State::Rising)
	{
		m_elapsed += dt;

		if (m_elapsed >= m_duration)
		{
			m_elapsed = 0.f;
			this->setOpenShade(false);
			//ת������״̬
			this->changeState(State::Walk);
		}
	}//����״̬
	else if (m_state == State::Walk)
	{
		this->updateWalkState(dt);
	}//����״̬
	else if (m_state == State::Dance || m_state == State::DanceDead)
	{
		m_elapsed += dt;

		if (m_elapsed >= m_duration)
		{
			m_elapsed = 0.f;
			State nextState;

			if (m_state == State::Dance)
				nextState = State::Walk;
			else if (m_state == State::DanceDead)
				nextState = State::WalkDead;
			//����״̬
			this->changeState(nextState);
		}
	}
	//����״̬
	else if (m_state == State::Attack)
	{
		if (m_pAim == nullptr || m_pAim->isDead())
		{
			this->clearAim();
			this->changeState(State::Walk);
		}
		else
		{
			this->eatAim(dt);
		}
	}
}

bool BackupDancer::isCanMove()const
{
	if (m_state == State::Walk || m_state == State::WalkDead)
		return true;

	return false;
}

void BackupDancer::onNormalDead()
{
	State state = State::None;

	if (m_state == State::Walk)
		state = State::WalkDead;
	else if (m_state == State::Attack)
		state = State::AttackDead;
	else if (m_state == State::Dance)
		state = State::DanceDead;

	if (state != State::None)
		this->changeState(state);
}

void BackupDancer::changeState(State state)
{
	//״̬û�з����ı䣬ֱ���˳�
	if (m_state == state)
		return ;

	m_state = state;
	string animationName;

	if (m_state == State::Rising)
	{
		//���ó���ʱ��
		m_duration = 0.4f;
		//����λ��
		auto size = this->getSprite()->getContentSize();
		auto pos = this->getSprite()->getPosition();

		this->getSprite()->setPosition(pos + Point(0.f,size.height/2));
		//������������
		MoveBy*move = MoveBy::create(m_duration,Point(0.f,-size.height/2));

		this->getSprite()->runAction(move);
	}
	else if (m_state == State::Walk)
	{
		animationName = StringUtils::format("%sWalk",m_zombieName.c_str());
		//���߼���
		m_duration = 3.f;
	}
	else if (m_state == State::Attack)
	{
		animationName = StringUtils::format("%sAttack",m_zombieName.c_str());
	}
	else if (m_state == State::Dance)
	{
		animationName = StringUtils::format("%sDancing",m_zombieName.c_str());
		//���輸��
		m_duration = 2.f;
	}
	else if (m_state == State::WalkDead)
	{
		animationName = StringUtils::format("%sLostHeadWalk",m_zombieName.c_str());

		this->showZombieHead();
	}
	else if (m_state == State::AttackDead)
	{
		animationName = StringUtils::format("%sLostHeadAttack",m_zombieName.c_str());
		
		this->showZombieHead();
	}
	else if (m_state == State::DanceDead)
	{
		animationName = StringUtils::format("%sLostHeadDancing",m_zombieName.c_str());
		
		this->showZombieHead();
	}
	if (animationName.empty())
	{
		return ;
	}

	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	ZombieBase::changeAnimation(animation);
}

void BackupDancer::showZombieHead()
{
	//����λ��
	Point bornPos = this->getPosition();
	Size size = this->getContentSize();

	bornPos.x += size.width/4.f;

	m_pDelegate->showZombieHead(this->getZombieName(),bornPos,this->getLocalZOrder(),false);
}

void BackupDancer::updateWalkState(float dt)
{
	m_elapsed += dt;
	//���ڹ���Ŀ��
	if (m_pAim != nullptr)
	{
		this->changeState(State::Attack);
		m_elapsed = 0.f;
	}
	else if (m_elapsed >= m_duration)
	{
		m_elapsed = 0.f;
		//TODO
		this->changeState(State::Dance);
	}
}