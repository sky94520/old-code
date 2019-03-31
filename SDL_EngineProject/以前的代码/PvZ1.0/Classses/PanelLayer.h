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
	Shovel*m_pShovel;//����
public:
	PanelLayer();
	~PanelLayer();
	CREATE_FUNC(PanelLayer);
	bool init();

	bool isClickedShovel(const Point&pos)const;

	Shovel*getShovel()const;
private:
	void updateSunNum(Object*);//���µ�ǰ̫������
};
#endif