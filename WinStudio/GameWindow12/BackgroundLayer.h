#ifndef __BackgroundLayer_H__
#define __BackgroundLayer_H__
#include "Object.h"
class BackgroundLayer:public Object
{
private:
	LPCWSTR m_textureID;
	POINT m_pos1;
	POINT m_pos2;
public:
	BackgroundLayer();
	~BackgroundLayer();
	BOOL load(LPCWSTR textureID);
	virtual void draw();
	virtual void update();
	virtual void clean();
};
#endif