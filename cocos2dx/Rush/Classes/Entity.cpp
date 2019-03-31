#include "Entity.h"

Entity::Entity():
	m_nID(0),m_nModelID(0),m_name(""),m_nHP(0),
	m_nDefense(0),m_nSpeed(0),m_nCurLevel(1),m_bIsDead(false)
{
	m_pSprite = NULL;
}
Entity::~Entity()
{
}
bool Entity::init()
{
	if(!Node::init())
		return false;
	return true;
}
Sprite*Entity::getSprite()
{
	return this->m_pSprite;
}
void Entity::bindSprite(Sprite*sprite)
{
	if(m_pSprite != NULL)
		this->removeChild(m_pSprite);
	this->m_pSprite = sprite;
	this->addChild(m_pSprite);
	setAnchorPoint(Point(0.5,0.5));
	Size size = m_pSprite->getContentSize();
	this->setContentSize(size);
	m_pSprite->setPosition(Point(size.width*0.5f,size.height*0.5f));

	onBindSprite();
}
void Entity::hurtMe(int nHurtValue)
{
	if(isDead())
		return ;
	//是否破除防御
	if(nHurtValue < getDefense())
		nHurtValue = 1;
	//当前HP
	int nCurHP = getHP();
	//被攻击后的HP
	int nAfterHP = nCurHP - nHurtValue;
	onHurt(nAfterHP);

	if(nAfterHP > 0)
		setHP(nAfterHP);
	else
	{
		m_bIsDead = true;
		onDead();
	}
}
bool Entity::isDead()
{
	return m_bIsDead;
}
void Entity::onDead()
{
}
void Entity::onHurt(int nHurtValue)
{
}
void Entity::onBindSprite()
{
}
Animation*Entity::createNormalAction(std::string format,int frameCountBegin,int frameCountEnd,int fps)
{
	Vector<SpriteFrame*> spriteFrames;
	for(int i=frameCountBegin;i<frameCountEnd;i++)
	{
		SpriteFrame*frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format(format.c_str(),i));
		spriteFrames.pushBack(frame);
	}
	return Animation::createWithSpriteFrames(spriteFrames,1.f/fps);
}