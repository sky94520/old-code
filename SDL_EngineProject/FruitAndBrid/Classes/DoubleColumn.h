#ifndef __DoubleColumn_H__
#define __DobuleColumn_H__
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;
class Column;
class DoubleColumn:public Node
{
private:
	Column*m_pTop;
	Column*m_pBottom;
public:
	DoubleColumn();
	~DoubleColumn();
	CREATE_FUNC(DoubleColumn);
	bool init();
	//重置，保证复用性
	void reset();
	//是否可用，即是否出界
	bool isAvaiable()const;
	//是否与该rect发生碰撞
	bool checkCollision(const Rect&rect);
};
#endif