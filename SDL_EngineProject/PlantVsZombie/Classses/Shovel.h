#ifndef __Shovel_H__
#define __Shovel_H__
#include "SDL_Engine/SDL_Engine.h"
#include "Entity.h"

using namespace SDL;
class Shovel : public Entity
{
private:
	//当前是否处于选中状态
	bool m_bSelected;
public:
	Shovel();
	~Shovel();
	CREATE_FUNC(Shovel);
	bool init();
	//是否选中
	bool isSelected()const;
	//设置为选中状态
	void selected();
	//设置为没选中状态
	void unselected();
};
#endif