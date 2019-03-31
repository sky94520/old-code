#ifndef __BackgroundLayer_H__
#define __BackgroundLayer_H__
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;
class BackgroundLayer:public SDL::Layer
{
private:
	Sprite*m_pBackground;
public:
	BackgroundLayer();
	~BackgroundLayer();
	CREATE_FUNC(BackgroundLayer);
	bool init();
};
#endif