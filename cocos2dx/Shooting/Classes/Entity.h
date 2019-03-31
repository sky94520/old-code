#ifndef __Entity_H__
#define __Entity_H__
#include<string>
#include "cocos2d.h"
USING_NS_CC;
class Entity:public Node
{
protected:
	Sprite*m_pSprite;
	Entity();
public:
	//´´½¨¶¯»­[begin,end)
	static Animate*createAnimate(const std::string&format,int begin,int end,float fps,unsigned int loops = -1);
public:
	void bindSprite(Sprite*pSprite);
	Sprite*getSprite()const;
};
#endif