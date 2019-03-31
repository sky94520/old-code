#ifndef __PanelLayer_H__
#define __PanelLayer_H__
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;
class PanelLayer:public Layer
{
private:
	LabelAtlas*m_pScore;
	LabelAtlas*m_pLevel;
public:
	PanelLayer();
	~PanelLayer();
	CREATE_FUNC(PanelLayer);
	bool init();
private:
	void updateSelf(Object*sender);
};
#endif