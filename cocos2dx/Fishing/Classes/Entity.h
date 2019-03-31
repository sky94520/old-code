#ifndef __Entity_H__
#define __Entity_H__
#include "cocos2d.h"
USING_NS_CC;
class Entity:public Node
{
protected:
	Sprite*m_pSprite;
public:
	Entity();
	~Entity();
	Sprite*getSprite()const;
	void bindSprite(Sprite*sprite);
	//´´½¨¶¯»­
	static Animate*createAnimate(std::string format,int begin,int end,float delayPerUnit,unsigned int loops=-1);
};
#endif