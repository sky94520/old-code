#ifndef __PanelLayer_H__
#define __PanelLayer_H__
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;
class GoldTimer;
class GoldCounter;
/*�ӿ�*/
class PanelLayerDelegate
{
public:
	virtual ~PanelLayerDelegate(){}
	virtual void pause()=0;
};
/*״̬������ʾ��ͣ��ť����*/
class PanelLayer:public Layer
{
private:
	PanelLayerDelegate*m_pDelegate;
	GoldCounter*m_pGoldCounter;
	GoldTimer*m_pGoldTimer;
public:
	PanelLayer();
	~PanelLayer();
	CREATE_FUNC(PanelLayer);
	bool init();
public:
	void setDelegate(PanelLayerDelegate*pDelegate);

	virtual void update(float dt);
private:
	void pauseCallback(Object*);
};
#endif