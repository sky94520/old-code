#include "Entity.h"
#include "FlyBehavior.h"

Entity::Entity()
	:m_pSprite(nullptr),m_nCurHp(0),m_nMaxHp(0)
	,m_curSpeed(0.f),m_nAtk(0)
	,m_pFlyBehavior(nullptr),m_bAlive(true)
{
}
Entity::~Entity()
{
	SDL_SAFE_DELETE(m_pFlyBehavior);
}
void Entity::bindSprite(Sprite*sprite)
{
	this->m_pSprite = sprite;
	this->addChild(m_pSprite);

	Size size = m_pSprite->getContentSize();

	m_pSprite->setPosition(size.width/2,size.height/2);
	this->setContentSize(size);
}
Sprite*Entity::getSprite()const
{
	return m_pSprite;
}
Animate*Entity::createAnimate(std::string format,int begin,int end,float delayPerUnit,unsigned int loops)
{
	vector<SpriteFrame*> frames;
	auto spriteFrameCache = Director::getInstance()->getSpriteFrameCache();
	for(int i=begin;i<=end;i++)
	{
		auto frame = spriteFrameCache->getSpriteFrameByName(StringUtils::format(format.c_str(),i));
		frames.push_back(frame);
	}
	Animation*animation = Animation::createWithSpriteFrames(frames,delayPerUnit,loops);
	if(loops == 1)
		animation->setRestoreOriginalFrame(true);
	return Animate::create(animation);
}
void Entity::hurt(int damage)
{
	//�����ʱ�Ѿ����������ٵ���
	if(this->isDead())
		return;
	int curHp = this->getCurHp();
	int afterHp = curHp - damage;
	//ֻҪ���˾͵����������
	onHurt(damage);
	setCurHp(afterHp);
	if(afterHp <= 0)
		onDead();//����ʱ����
}
bool Entity::isDead()const
{
	return m_nCurHp <= 0;
}
void Entity::setFlyBehavior(FlyBehavior*behavior)
{
	//���б�Ҫ���ڴ洦��
	SDL_SAFE_DELETE(m_pFlyBehavior);

	m_pFlyBehavior = behavior;
}
void Entity::update(float dt)
{
	m_pFlyBehavior->fly(this);
}

void Entity::onBindSprite()
{
}
void Entity::onHurt(int damage)
{
}
void Entity::onDead()
{
}