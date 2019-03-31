#include "PaperZombie.h"

PaperZombie::PaperZombie()
	:m_bIsAngry(false)
{
}

PaperZombie::~PaperZombie()
{
}

PaperZombie*PaperZombie::create(const string&zombieName)
{
	auto zombie = new PaperZombie();

	if (zombie && zombie->init(zombieName))
		zombie->autorelease();
	else
		SDL_SAFE_DELETE(zombie);

	return zombie;
}

bool PaperZombie::init(const string&zombieName)
{
	//��������
	this->setZombieName(zombieName);
	//��ȡվ��״̬��ͼ
	int status = m_bIsAngry ? 0 : 1;
	auto animationName = StringUtils::format("%sWalk%d",m_zombieName.c_str(),status);

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

void PaperZombie::changeState(State state)
{
	//״̬û�з����ı䣬ֱ���˳�
	if (m_state == state)
		return ;

	m_state = state;
	string animationName;
	int status = m_bIsAngry ? 0 : 1;

	if (m_state == State::Walk)
	{
		animationName = StringUtils::format("%sWalk%d",m_zombieName.c_str(),status);
	}
	else if (m_state == State::Attack)
	{
		animationName = StringUtils::format("%sAttack%d",m_zombieName.c_str(),status);
	}
	else if (m_state == State::WalkDead)
	{
		animationName = StringUtils::format("%sLostHeadWalk%d",m_zombieName.c_str(),status);

		this->showZombieHead();
	}
	else if (m_state == State::AttackDead)
	{
		animationName = StringUtils::format("%sLostHeadAttack%d",m_zombieName.c_str(),status);
		
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

void PaperZombie::showZombieHead()
{
	//����λ��
	Point bornPos = this->getPosition();
	Size size = this->getContentSize();

	m_pDelegate->showZombieHead(this->getZombieName(),bornPos,this->getTag(),false);
}

float PaperZombie::getCurSpeed()const
{
	auto speed = ZombieBase::getCurSpeed();

	if (m_bIsAngry)
		speed *= 2.f;

	return speed;
}

void PaperZombie::onGarnishryDead()
{
	//��ǰ����������ִ��
	if (this->getHitPoint() <= 0)
		return ;

	m_bIsAngry = true;
	//��Ϊվ��״̬
	this->changeState(State::Idle);
	//ֹͣԭ�ȶ���
	m_pSprite->stopActionByTag(ANIMATION_TAG);
	//��ֽ���䶯��
	auto animationName = "PaperZombieLostNewspaper";
	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	Animate*animate = Animate::create(animation);
	auto speed = Speed::create(animate,1.f);
	speed->setTag(ANIMATION_TAG);

	if (this->isDuringDeceleration())
		speed->setSpeed(0.7f);

	DelayTime*delay = DelayTime::create(animate->getDuration());
	CallFunc*end = CallFunc::create([this]()
	{
		this->changeState(State::Walk);
	});
	auto seq = Sequence::createWithTwoActions(delay,end);

	this->stopAllActions();
	//��ʼ����
	m_pSprite->runAction(speed);
	this->runAction(seq);
}

void PaperZombie::onCRPDead()
{
	this->setDead(true);

	bool flipX = this->getSprite()->isFlipX();
	//��ʾ��������
	m_pDelegate->showZombieDie(this->getZombieName(),this->getPosition(),this->getTag(),flipX);
}

void PaperZombie::onButterDebuffEnter(const Point&pos)
{
	Zombie::onButterDebuffEnter(pos - Point(-15.f,0.f));
}

void PaperZombie::onButterDebuffExit()
{
	Zombie::onButterDebuffExit();
}