#ifndef __BackgroundLayer_H__
#define __backgroundLayer_H__
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;
/*±³¾°²ã*/
class BackgroundLayer:public Layer
{
	SDL_SYNTHESIZE(float,m_speed,Speed);//ÒÆ¶¯ËÙ¶È
private:
	Sprite*m_pSprite1;
	Sprite*m_pSprite2;
public:
	BackgroundLayer();
	~BackgroundLayer();
	CREATE_FUNC(BackgroundLayer);
	bool init();
public:
	virtual void update(float dt);
};
#endif