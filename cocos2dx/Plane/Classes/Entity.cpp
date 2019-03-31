#include "Entity.h"
Entity::Entity()
	:m_pSprite(nullptr),m_nHitPoints(0),m_nCurHP(0),m_nDamage(0)
	,m_nDefense(0)
{
}
Entity::~Entity()
{
}
void Entity::bindSprite(Sprite*sprite)
{
	if(m_pSprite == sprite)
		return;
	if(m_pSprite)
		m_pSprite->removeFromParent();
	m_pSprite = sprite;
	this->setAnchorPoint(ccp(0.5f,0.5f));
	this->setContentSize(m_pSprite->getContentSize());
	m_pSprite->setPosition(0.5*getContentSize().width,0.5*getContentSize().height);
	this->addChild(m_pSprite);
}
Sprite*Entity::getSprite()const
{
	return m_pSprite;
}
Animate*Entity::createAnimate(std::string format,int begin,int end,float delayPerUnit,unsigned int loops)
{
	Vector<SpriteFrame*> frames;
	auto spriteFrameCache = SpriteFrameCache::getInstance();
	//�����Դ
	//spriteFrameCache->addSpriteFramesWithFile(xml,png);
	for(int i=begin;i<=end;i++)
	{
		auto frame = spriteFrameCache->getSpriteFrameByName(StringUtils::format(format.c_str(),i));
		frames.pushBack(frame);
	}
	Animation*animation = Animation::createWithSpriteFrames(frames,delayPerUnit,loops);
	if(loops == 1)
		animation->setRestoreOriginalFrame(true);
	return Animate::create(animation);
}
bool Entity::isAlive()const
{
	return m_nCurHP > 0;
}
void Entity::hurt(int damage)
{
	//�۳���������ĵ�ǰHP
	int hp = m_nCurHP - damage+m_nDefense;
	//�������˺��һϵ���߼�
	onHurt();
	//С��0.����
	if(hp <= 0)
	{
		Entity::dead();
		hp = 0;//ʹѪ����Ϊ0
	}
	setCurHP(hp);
}
//todo
void Entity::dead()
{
	onDead();
}