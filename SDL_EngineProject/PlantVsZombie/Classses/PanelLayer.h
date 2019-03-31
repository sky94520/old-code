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
	//��ȡ��������屳��
	Point getSunBgPosition();
	//ѡ���˲���
	void seletcShovel();
	//ȡ��ѡ�в���
	void unselectShovel();
	bool isClickShovel(const Point&pos)const;
	//��ȡ����
	bool isSelectedShovel();
};
#endif