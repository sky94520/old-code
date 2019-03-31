#ifndef __Entity_H__
#define __Entity_H__

#include "cocos2d.h"
#include "Controller.h"
#include "ControllerListener.h"

USING_NS_CC;

class Entity : public Node,public ControllerListener
{
public:
	void bindSprite(Sprite*sprite);

	//���ÿ�����
	void setController(Controller*controller);
	//ʵ��SimpleMoveConrtoller�ӿڵķ���
	virtual void setTagPosition(int x,int y);
	virtual Point getTagPosition();

protected:
	Sprite*m_sprite;

	Controller*m_controller;

};
#endif