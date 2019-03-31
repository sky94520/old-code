#ifndef __Player_H__
#define __Player_H__
#include "Object.h"
#include<Windows.h>
class Player:public Object
{
private:
	POINT m_position;//Î»ÖÃ
	SIZE m_size;//Åö×²Ãæ»ý
	LPCWSTR m_textureID;
	LPCWSTR m_textureMask;//ÃÉ°æ
public:
	Player();
	~Player();

	BOOL load(LPCWSTR textureID,LPCWSTR textureMask);

	virtual void draw();
	virtual void update();
	virtual void clean();
};
#endif