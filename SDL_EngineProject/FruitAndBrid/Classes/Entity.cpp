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
	this->setContentSize(m_pSprite->getContentSize());
	this->addChild(m_pSprite);
}
Sprite*Entity::getSprite()const
{
	return m_pSprite;
}
Animate*Entity::createAnimate(std::string format,int begin,int end,float delayPerUnit,unsigned int loops)
{
	std::vector<SpriteFrame*> frames;
	auto spriteFrameCache = TheDirector::getInstance()->getSpriteFrameCache();
	//添加资源
	//spriteFrameCache->addSpriteFramesWithFile(xml,png);
	for(int i=begin;i<=end;i++)
	{
		auto frame = spriteFrameCache->getSpriteFrameByName(StringUtils::format(format.c_str(),i));
		frames.push_back(frame);
	}
	Animation*animation = Animation::createWithSpriteFrames(frames,delayPerUnit,loops);
	return Animate::create(animation);
}
std::vector<SpriteFrame*> Entity::splitSpriteFrame(const std::string&picture,int x,int y,int w,int h,int count)
{
	SpriteFrameCache*spriteFrameCache = TheDirector::getInstance()->getSpriteFrameCache();
	//是否已经加载该图片
	std::vector<SpriteFrame*> frames;
	for(int i=0;i<count;i++)
	{
		SpriteFrame * clip = SpriteFrame::create(picture,Rect(x+i*w,y,w,h));
		frames.push_back(clip);
	}
	return frames;
}