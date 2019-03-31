#ifndef __PanelLayer_H__
#define __PanelLayer_H__
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;
class PanelLayer:public Layer
{
private:
	LabelAtlas*m_pScoreLabel;
	LabelAtlas*m_pLifeLabel;
	LabelAtlas*m_pBulletLabel;
	LabelAtlas*m_pSpeedLabel;
public:
	PanelLayer();
	~PanelLayer();
	CREATE_FUNC(PanelLayer);
	bool init();
private:
	void updateDynamicData(EventCustom*custom);
	void updatePlayer(EventCustom*custom);
};
#endif