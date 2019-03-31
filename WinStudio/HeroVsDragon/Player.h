#ifndef __Player_H__
#define __Player_H__
#include "Entity.h"
class Player:public Entity
{
public:
	Player();
	~Player();

	virtual BOOL load(int x,int y,int w,int h,LPCWSTR textureID);
	virtual void draw(HDC hdc);
	virtual void update();
	virtual void clean();
};
#endif