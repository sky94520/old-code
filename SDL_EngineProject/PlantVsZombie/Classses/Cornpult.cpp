#include "Cornpult.h"

Cornpult::Cornpult()
	:m_bIsButter(false)
{
}

Cornpult::~Cornpult()
{
}

Cornpult*Cornpult::create(const string&plantName)
{
	auto plant = new Cornpult();

	if (plant && plant->init(plantName))
		plant->autorelease();
	else
		SDL_SAFE_DELETE(plant);

	return plant;
}

bool Cornpult::init(const string&plantName)
{
	this->setPlantName(plantName);
	//设置正常动画
	int index = m_bIsButter ? 1 : 0;
	auto animationName = StringUtils::format("%s%d",plantName.c_str(),index);
	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	//设置贴图
	auto firstFrame = animation->getFrames().front()->getSpriteFrame();
	m_pSprite = Sprite::createWithSpriteFrame(firstFrame);
	
	auto size = m_pSprite->getContentSize();
	//设置位置
	m_pSprite->setPosition(Point(size.width/3.f,size.height/4.f));

	this->setContentSize(size);
	this->addChild(m_pSprite);
	//设置运行动画
	Animate*animate = Animate::create(animation);
	animate->setTag(ANIMATION_TAG);
	this->getSprite()->runAction(animate);
	//设置状态为正常状态
	m_state = State::Normal;

	return true;
	return true;
}

void Cornpult::changeState(State state)
{
	if (m_state == state)
		return ;

	m_state = state;

	string animationName;
	auto plantName = this->getPlantName();
	Animation*animation = nullptr;
	//根据是否是黄油有两个不同的动画
	int index = m_bIsButter ? 1 : 0;

	if (state == State::Normal)
	{
		animationName = StringUtils::format("%s%d",plantName.c_str(),index);
		//停止原先的动画
		this->getSprite()->stopActionByTag(ANIMATION_TAG);

		animation = AnimationCache::getInstance()->getAnimation(animationName);
	}
	else if (state == State::Attack)
	{
		animationName = StringUtils::format("%sAttack%d",plantName.c_str(),index);
		//停止原先的动画
		this->getSprite()->stopActionByTag(ANIMATION_TAG);
	
		animation = AnimationCache::getInstance()->getAnimation(animationName);

		m_duration = animation->getDuration();
	}
	else if (state == State::AttackEnd)
	{
		animationName = StringUtils::format("%sAttackEnd",plantName.c_str());
		//停止原先的动画
		this->getSprite()->stopActionByTag(ANIMATION_TAG);
	
		animation = AnimationCache::getInstance()->getAnimation(animationName);
	
		m_duration = animation->getDuration();
	}
	if (animation != nullptr)
	{
		auto animate = Animate::create(animation);
		animate->setTag(ANIMATION_TAG);

		this->getSprite()->runAction(animate);
	}
}

void Cornpult::shoot()
{
	//发射子弹
	auto damage = m_bIsButter ? m_nDamage * 4 : m_nDamage;

	auto pos = this->getPosition();
	auto row = m_pCarrier->getRow();

	Size size = this->getContentSize();

	pos.y -= size.height/2.f;

	m_pDelegate->addCornpultBullet(m_pAimZombie,m_bIsButter,damage,row,pos);
}

void Cornpult::shootEndHook()
{
	//进行攻击判断
	double scope = RANDOM_0_1();

	m_bIsButter = scope < 0.8 ? false : true;
}