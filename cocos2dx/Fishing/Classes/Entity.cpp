#include "Entity.h"
Entity::Entity()
	:m_pSprite(nullptr)
{
}
Entity::~Entity()
{
}
void Entity::bindSprite(Sprite*sprite)
{
	if(m_pSprite)
		m_pSprite->removeFromParent();
	m_pSprite = sprite;

	Size size = m_pSprite->getContentSize();
	this->setContentSize(size);
	this->setAnchorPoint(Point(0.5f,0.5f));
	m_pSprite->setPosition(size.width*0.5f,size.height * 0.5);

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
	//Ìí¼Ó×ÊÔ´
	for(int i=begin;i<=end;i++)
	{
		auto frame = spriteFrameCache->getSpriteFrameByName(StringUtils::format(format.c_str(),i));
		frames.pushBack(frame);
	}
	Animation*animation = Animation::createWithSpriteFrames(frames,delayPerUnit,loops);
	return Animate::create(animation);
}