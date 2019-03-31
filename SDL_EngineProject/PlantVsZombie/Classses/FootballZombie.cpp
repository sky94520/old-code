#include "FootballZombie.h"
#include "Garnishry.h"

FootballZombie::FootballZombie()
{
}

FootballZombie::~FootballZombie()
{
}

FootballZombie*FootballZombie::create(const string& zombieName)
{
	auto zombie = new FootballZombie();

	if (zombie && zombie->init(zombieName))
		zombie->autorelease();
	else
		SDL_SAFE_DELETE(zombie);

	return zombie;
}

bool FootballZombie::init(const string& zombieName)
{
	//��������
	this->setZombieName(zombieName);
	//��ȡվ��״̬��ͼ
	auto animationName = StringUtils::format("%sWalk",m_zombieName.c_str());

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
	Speed*speed = Speed::create(animate,1.f);
	
	speed->setTag(ANIMATION_TAG);

	m_pSprite->runAction(speed);
	//����Ϊ����״̬
	m_state = State::Walk;

	return true;
}

void FootballZombie::changeState(State state)
{
	//״̬û�з����ı䣬ֱ���˳�
	if (m_state == state)
		return ;

	m_state = state;
	string animationName;
	bool bGarnishryDead = true;
	//��Ʒ����
	if (m_pGarnishry != nullptr && m_pGarnishry->getHitPoint() > 0)
		bGarnishryDead = false;

	if (m_state == State::Walk)
	{
		if (!bGarnishryDead)
			animationName = StringUtils::format("%sWalk",m_zombieName.c_str());
		else
			animationName = StringUtils::format("%sOrnLostWalk",m_zombieName.c_str());
	}
	else if (m_state == State::Attack)
	{
		if (!bGarnishryDead)
			animationName = StringUtils::format("%sAttack",m_zombieName.c_str());
		else
			animationName = StringUtils::format("%sOrnLostAttack",m_zombieName.c_str());
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
	//�ı��״̬û�ж�������ֱ�ӷ���
	if (animationName.empty())
	{
		return;
	}
	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	ZombieBase::changeAnimation(animation);
}

void FootballZombie::onGarnishryDead()
{
	//��������
	auto oldState = m_state;

	m_state = State::None;

	this->changeState(oldState);
	//��ʾ·�ϵ��䶯��
	Point pos = this->getPosition();
	Size size = this->getContentSize();

	pos.x += size.width/4;
	pos.y -= size.height/2;

	m_pDelegate->showGarnishryFallAction(m_pGarnishry,pos,this->getTag(),false);
}

void FootballZombie::showZombieHead()
{
	Zombie::showZombieHead();
}

void FootballZombie::onCRPDead()
{
	auto pos = this->getPosition();
	auto localZOrder = this->getLocalZOrder();
	auto flipX = this->getSprite()->isFlipX();

	m_pDelegate->showZombieDie(this->getZombieName(),pos,localZOrder,flipX);
}

void FootballZombie::onButterDebuffEnter(const Point&pos)
{
	Zombie::onButterDebuffEnter(pos);
}

void FootballZombie::onButterDebuffExit()
{
	Zombie::onButterDebuffExit();
}