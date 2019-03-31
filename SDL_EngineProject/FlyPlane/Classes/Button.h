#ifndef __Button_H__
#define __Button_H__
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;
class Button:public Node
{
	SDL_SYNTHESIZE(SDL_FingerID,m_fingerId,FingerId);
private:
	ccMenuCallback m_callback;
	Sprite*m_pNormalSprite;
	Sprite*m_pSelectedSprite;
public:
	Button();
	~Button();
	static Button*create(Sprite*normalSprite,Sprite*selectedSprite);
	bool init(Sprite*normalSprite,Sprite*selectedSprite);

	void setCallback(const ccMenuCallback&callback);
	void selected();
	void activate();
	void unselected();
};
#endif