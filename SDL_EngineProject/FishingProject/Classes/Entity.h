#ifndef __Entity_H__
#define __Entity_H__
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;
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
	static std::vector<SpriteFrame*> splitSpriteFrame(const std::string&picture,int x,int y,int w,int h,int count);
};
#endif