#ifndef __GameLayer_H__
#define __GameLayer_H__
#include "SDL_Engine/SDL_Engine.h"
#include "Fork.h"

using namespace SDL;
class GameLayer:public Layer
{
private:
	Fork*m_pFork;
public:
	GameLayer();
	~GameLayer();
	CREATE_FUNC(GameLayer);
	bool init();

	Fork*getFork()const;
};
#endif