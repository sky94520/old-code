#ifndef __Monster_H__
#define __Monster_H__
#include "Entity.h"

class Monster:public Entity
{
public:
	Monster();
	~Monster();

	virtual BOOL load(int x,int y,int w,int h,LPCWSTR textureID);
	virtual void draw(HDC hdc);
	virtual void update();
	virtual void clean();
};
#endif