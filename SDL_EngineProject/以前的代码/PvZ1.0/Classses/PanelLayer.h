#ifndef __PanelLayer_H__
#define __PanelLayer_H__
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;
class Shovel;
class PanelLayer:public Layer
{
private:
	Sprite*m_pSunBackground;
	LabelAtlas*m_pSunNumLabel;
	Shovel*m_pShovel;//铲子
public:
	PanelLayer();
	~PanelLayer();
	CREATE_FUNC(PanelLayer);
	bool init();

	bool isClickedShovel(const Point&pos)const;

	Shovel*getShovel()const;
private:
	void updateSunNum(Object*);//更新当前太阳数量
};
#endif