#ifndef __VirtualStick_H__
#define __VirtualStick_H__
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;

class VirtualStick:public Node
{
	SDL_SYNTHESIZE(int,m_fingerId,FingerId);
private:
	Sprite*m_pStick;
	Sprite*m_pStickBackground;
public:
	VirtualStick();
	~VirtualStick();
	static VirtualStick*create(Sprite*stick,Sprite*bg);
	bool init(Sprite*stick,Sprite*bg);
	void selected(const Point&pos);
	Point getDirection();
	void unselected();
};
#endif
