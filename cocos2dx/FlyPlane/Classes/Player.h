#ifndef __Player_H__
#define __Player_H__
#include "Entity.h"
#include "TouchListener.h"
#include "TouchController.h"

class Player : public Entity,public TouchListener
{
public:
	virtual bool init();
	CREATE_FUNC(Player);

	Player();
	~Player();

	virtual Point getTagPosition();
	virtual void setTagPosition(Point point);

	void setTouchController(TouchController*iTouchController);

private:
	TouchController*m_touchController;
};
#endif