#ifndef __PanelLayer_H__
#define __PanelLayer_H__
#include<string>
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;
using namespace std;
class PanelLayer:public Layer
{
private:
	LabelAtlas*m_pLives;
	LabelAtlas*m_pGold;
public:
	PanelLayer();
	~PanelLayer();
	CREATE_FUNC(PanelLayer);
	bool init();
private:
	void updateSelf(Object*sender);
};
#endif