#ifndef __PanelLayer_H__
#define __PanelLayer_H__
#include<string>
#include "SDL_Engine/SDL_Engine.h"

using namespace SDL;
using namespace std;

class PanelLayer:public Layer
{
private:
	LabelDotChar*m_pScoreLabel;
	LabelDotChar*m_pCoinLabel;
	LabelDotChar*m_pLevelLabel;
	LabelDotChar*m_pLifeLabel;
	LabelDotChar*m_pTimeLabel;
public:
	PanelLayer();
	~PanelLayer();
	CREATE_FUNC(PanelLayer);
	bool init();
public:
	void flowTextAction(Layer*parent,const string&text,const Point&positon);//Ʈ��Ч��
	void blockBrokenAction(Layer*parent,Sprite*sprite);//ש������Ч��
	void goldAction(Layer*parent,const Point&position);//��ý��Ч��
private:
	void scoreCallback(EventCustom*eventCustom);
	void coinCallback(EventCustom*eventCustom);
	void levelCallback(EventCustom*eventCustom);
	void lifeCallback(EventCustom*eventCustom);
	void timeCallback(EventCustom*eventCustom);
};
#endif