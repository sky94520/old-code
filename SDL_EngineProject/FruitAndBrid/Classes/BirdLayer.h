#ifndef __BirdLayer_H__
#define __BirdLayer_H__
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;
class Bird;

class BirdLayer:public Layer
{
private:
	Bird*m_pBird;
public:
	BirdLayer();
	~BirdLayer();
	CREATE_FUNC(BirdLayer);
	bool init();
public:
	void update(float dt);
	void birdFly(SDL_Keycode keyCode,SDL_Event*event);

	Bird*getBird();
};
#endif