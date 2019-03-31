#ifndef __Entity_H__
#define __Entity_H__
#include<string>
#include "SDL_Engine/SDL_Engine.h"

using namespace SDL;
using namespace std;

class Entity:public Node
{
	SDL_BOOL_SYNTHESIZE(m_bOpenShade,OpenShade);//�Ƿ�������
public:
	static const int ANIMATION_TAG;
	static const int ACTION_TAG;
protected:
	Sprite* m_pSprite;
public:
	Entity();
	~Entity();
	Sprite* getSprite() const;
	void unbingSprite();
	//��bind��ͬ���˺������ı�content size
	void setSprite(Sprite* sprite);
	void bindSprite(Sprite* sprite);

	Sprite* bindSpriteWithSpriteFrame(SpriteFrame* spriteFrame);
	Sprite* bindSpriteWithSpriteFrameName(const string& spriteName);
	//��animation �ĵ�һ֡Ϊ��ͼ �������иö���
	Sprite* bindSpriteWithAnimate(Animate* animate);
	//��������
	static Animate* createAnimate(std::string format,int begin, int end, float delayPerUnit, unsigned int loops = -1);

	virtual void visit();
};
#endif