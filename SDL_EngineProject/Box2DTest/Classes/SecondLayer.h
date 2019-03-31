#ifndef __SecondLayer_H__
#define __SecondLayer_H__
#include "SDL_Engine/SDL_Engine.h"

USING_NS_SDL;

class Text;

class SecondLayer : public Layer
{
private:
	Text* m_pText;
public:
	static Scene* createScene();

	SecondLayer();
	~SecondLayer();
	CREATE_FUNC(SecondLayer);
	bool init();

	void update(float dt);

	virtual bool onTouchBegan(Touch* touch, SDL_Event* event);
};
#endif