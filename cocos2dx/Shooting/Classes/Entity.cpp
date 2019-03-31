#include "Entity.h"
Entity::Entity()
	:m_pSprite(nullptr)
{
}
Animate*Entity::createAnimate(const std::string&format,int begin,int end,float fps,unsigned int loops)
{
	SpriteFrameCache*cache = SpriteFrameCache::getInstance();
	Vector<SpriteFrame*> frameVec;
	SpriteFrame*frame = NULL;
	for(int i=begin;i<end;i++)
	{
		frame = cache->getSpriteFrameByName(StringUtils::format(format.c_str(),i));
		frameVec.pushBack(frame);
	}
	Animation*animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(loops);
	animation->setRestoreOriginalFrame(true);
	animation->setDelayPerUnit(fps);

	return Animate::create(animation);
}
void Entity::bindSprite(Sprite*pSprite)
{
	if(m_pSprite == pSprite)
		return;
	CC_SAFE_RETAIN(pSprite);
	if(m_pSprite)
		m_pSprite->removeFromParent();
	m_pSprite = pSprite;
	setContentSize(m_pSprite->getContentSize());
	this->setAnchorPoint(ccp(0.5f,0.5f));
	this->addChild(m_pSprite);
}
Sprite*Entity::getSprite()const
{
	return m_pSprite;
}