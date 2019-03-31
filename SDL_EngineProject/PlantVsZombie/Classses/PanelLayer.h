#ifndef __PanelLayer_H__
#define __PanelLayer_H__

#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;
class Shovel;

class PanelLayer : public Layer
{
private:
	LabelAtlas*m_pSunLabel;
	Sprite*m_pSunBg;
	Sprite*m_pShovelBg;
	Shovel*m_pShovel;
public:
	PanelLayer();
	~PanelLayer();
	CREATE_FUNC(PanelLayer);
	bool init();

	void updateUI();
	void updateSun();
	//获取阳光计数板背景
	Point getSunBgPosition();
	//选中了铲子
	void seletcShovel();
	//取消选中铲子
	void unselectShovel();
	bool isClickShovel(const Point&pos)const;
	//获取铲子
	bool isSelectedShovel();
};
#endif