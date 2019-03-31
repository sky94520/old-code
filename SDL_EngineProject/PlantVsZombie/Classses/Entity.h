#ifndef __Entity_H__
#define __Entity_H__
#include<string>
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;
using namespace std;

class Entity:public Node
{
	SDL_BOOL_SYNTHESIZE(m_bOpenShade,OpenShade);//是否开启遮罩
protected:
	Sprite*m_pSprite;
public:
	Entity();
	~Entity();
	Sprite*getSprite()const;
	//和bind不同，此函数不改变content size
	void setSprite(Sprite*sprite);
	void bindSprite(Sprite*sprite);

	Sprite* bindSpriteWithSpriteFrame(SpriteFrame*spriteFrame);
	Sprite* bindSpriteWithSpriteFrameName(const string&spriteName);
	//以animation 的第一帧为贴图 并且运行该动画
	Sprite* bindSpriteWithAnimate(Animate*animate);
	//创建动画
	static Animate*createAnimate(std::string format,int begin,int end,float delayPerUnit,unsigned int loops=-1);

	virtual void visit();
};
#endif