#ifndef __EventLayer_H__
#define __EventLayer_H__
#include <cmath>
#include <map>
#include "SDL_Engine/SDL_Engine.h"

using namespace std;
using namespace SDL;

enum class Direction;

class EventLayer : public Layer
{
protected:
	virtual void onKeyPressed(SDL_Keycode,SDL_Event*) = 0;
	virtual void onKeyReleased(SDL_Keycode,SDL_Event*) = 0;
};
//键盘事件层
class KeyboardEventLayer : public EventLayer
{
private:
	map<Direction, Uint32> m_keyStates;//保留方向按键
public:
	KeyboardEventLayer();
	~KeyboardEventLayer();
	CREATE_FUNC(KeyboardEventLayer);
	bool init();

	void update(float dt);
protected:
	virtual void onKeyPressed(SDL_Keycode,SDL_Event*);
	virtual void onKeyReleased(SDL_Keycode,SDL_Event*);
	Direction getDirecton(SDL_Keycode keycode);
};
#endif