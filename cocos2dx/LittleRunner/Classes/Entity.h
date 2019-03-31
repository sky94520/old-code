#ifndef __Entity_H__
#define __Entity_H__
#include "cocos2d.h"

USING_NS_CC;
class Entity : public Node
{
public:
	Entity();
	~Entity();
	//��ȡ�������
	Sprite*getSprite();
	//�ﶥ�������
	void bindSprite(Sprite*sprite);
protected:
	Sprite*m_sprite;
};
#endif