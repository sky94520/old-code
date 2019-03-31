#include "ScreenDoorZombie.h"

ScreenDoorZombie::ScreenDoorZombie()
{
}

ScreenDoorZombie::~ScreenDoorZombie()
{
}

ScreenDoorZombie* ScreenDoorZombie::create(const string& zombieName)
{
	auto zombie = new ScreenDoorZombie();

	if (zombie && zombie->init(zombieName))
		zombie->autorelease();
	else
		SDL_SAFE_DELETE(zombie);

	return zombie;
}

bool ScreenDoorZombie::init(const string& zombieName)
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

void ScreenDoorZombie::onGarnishryDead()
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

void ScreenDoorZombie::changeState(State state)
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

		animationName = StringUtils::format("%sLostHeadWalk",m_zombieName.c_str());
	}
	else if (m_state == State::AttackDead)
	{
		this->showZombieHead();

		animationName = StringUtils::format("%sLostHeadAttack",m_zombieName.c_str());
	}
	if (animationName.empty())
	{
		return;
	}
	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	ZombieBase::changeAnimation(animation);
}

void ScreenDoorZombie::judgeInnerSpritePos()
{
}