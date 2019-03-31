#include "ConeheadZombie.h"

ConeheadZombie::ConeheadZombie()
	:m_bGarnishryDead(false)
{
}

ConeheadZombie::~ConeheadZombie()
{
}

ConeheadZombie*ConeheadZombie::create(const string&zombieName)
{
	auto zombie = new ConeheadZombie();

	if (zombie && zombie->init(zombieName))
		zombie->autorelease();
	else
		SDL_SAFE_DELETE(zombie);

	return zombie;
}

bool ConeheadZombie::init(const string&zombieName)
{
	this->setZombieName(zombieName);
	//��ȡվ��״̬��ͼ
	auto animationName = StringUtils::format("%sWalk",m_zombieName.c_str());
	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	//������ͼ
	auto firstFrame = animation->getFrames().front()->getSpriteFrame();

	this->bindSpriteWithSpriteFrame(firstFrame);
	//��΢����һ��λ��
	this->judgeInnerSpritePos();
	//����վ������
	auto animate = Animate::create(animation);
	Speed*speed = Speed::create(animate,1.f);
	speed->setTag(ANIMATION_TAG);

	m_pSprite->runAction(speed);
	//����Ϊ����״̬
	m_state = State::Walk;

	return true;
}

void ConeheadZombie::onGarnishryDead()
{
	//��������
	this->setZombieName(m_nextZombieName);
	m_bGarnishryDead = true;

	auto oldState = m_state;

	m_state = State::None;
	//��΢����λ��
	this->judgeInnerSpritePos();

	this->changeState(oldState);
	//��ʾ·�ϵ��䶯��
	Point pos = this->getPosition();
	Size size = this->getContentSize();

	pos.x += size.width/4;
	pos.y -= size.height/2;

	m_pDelegate->showGarnishryFallAction(m_pGarnishry,pos,this->getTag(),false);
}

void ConeheadZombie::setSpriteFlipX(bool flipX)
{
	this->getSprite()->setFlipX(flipX);

	this->judgeInnerSpritePos();
}

void ConeheadZombie::changeState(State state)
{
	//״̬û�з����ı䣬ֱ���˳�
	if (m_state == state)
		return ;
	//�����Ʒ�Ѿ�����������ø���ķ���
	if (m_bGarnishryDead)
	{
		Zombie::changeState(state);
		return;
	}
	m_oldState = m_state;
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
	else if (m_state == State::WalkDead)
	{
		this->showZombieHead();
	}
	else if (m_state == State::AttackDead)
	{
		animationName = "ZombieLostHeadAttack";
		
		this->showZombieHead();
	}
	if (animationName.empty())
	{
		return;
	}
	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	ZombieBase::changeAnimation(animation);
}

void ConeheadZombie::showZombieHead()
{
	//����λ��
	Point bornPos = this->getPosition();
	Size size = this->getContentSize();
	bool flipX = this->getSprite()->isFlipX();

	if (flipX)
		bornPos.x -= size.width/4.f;
	else
		bornPos.x += size.width/3.f;

	m_pDelegate->showZombieHead(this->getZombieName(),bornPos,this->getTag(),flipX);
}

void ConeheadZombie::judgeInnerSpritePos()
{
	Size size = this->getContentSize();
	bool flipX = m_pSprite->isFlipX();

	Point pos;
	//�Խ�ʬ�ڲ����������΢����
	if (m_bGarnishryDead)
	{
		if (flipX)
			pos = Point(size.width/2.f + 45.f,size.height/2.f);
		else
			pos = Point(size.width/2.f + 15.f,size.height/2.f);
	}
	else
	{
		if (flipX)
			pos = Point(size.width/2.f + 60.f,size.height/2.f);
		else
			pos = Point(size.width/2.f,size.height/2.f);
	}

	m_pSprite->setPosition(pos);
}

void ConeheadZombie::onButterDebuffEnter(const Point&pos)
{
	auto startPos = pos;

	if (!m_bGarnishryDead)
	{
		startPos += Point(15.f,8.f);
	}
	Zombie::onButterDebuffEnter(startPos);
}

void ConeheadZombie::onButterDebuffExit()
{
	Zombie::onButterDebuffExit();
}