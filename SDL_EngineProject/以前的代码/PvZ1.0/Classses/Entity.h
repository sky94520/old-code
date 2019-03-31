#ifndef __Entity_H__
#define __Entity_H__
#include<string>
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;
class Entity:public SDL::Node
{
protected:
	Sprite*m_pSprite;
public:
	Entity():m_pSprite(nullptr){}
	~Entity(){}
	Sprite*getSprite()const
	{
		return m_pSprite;
	}
	void bindSprite(Sprite*sprite)
	{
		if(m_pSprite)
		{
			m_pSprite->removeFromParent();
		}
		m_pSprite = sprite;
		//设置大小
		this->setContentSize(sprite->getContentSize());
		this->addChild(sprite);
	}
	static Animate*createAnimation(std::string format,int begin,int end,float delayPerUint,unsigned int loops)
	{
		std::vector<SpriteFrame*> frames;
		auto spriteFrameCache = TheDirector::getInstance()->getSpriteFrameCache();
		//添加资源
		//spriteFrameCache->addSpriteFramesWithFile(xml,png);
		for(int i=begin;i<=end;i++)
		{
			/*char text[50];
			sprintf(text,format.c_str(),i);*/
			std::string text = StringUtils::format(format.c_str(),i);
			auto frame = spriteFrameCache->getSpriteFrameByName(text);
			frames.push_back(frame);
		}
		Animation*animation = Animation::createWithSpriteFrames(frames,delayPerUint,loops);
		return Animate::create(animation);
	}
};
#endif