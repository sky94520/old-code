#ifndef __PanelLayer_H__
#define __PanelLayer_H__
#include "cocos2d.h"
USING_NS_CC;
class PanelLayerDelegate
{
public:
	virtual ~PanelLayerDelegate(){}
	virtual void gamePause()=0;
};
class PanelLayer:public Layer
{
private:
	LabelAtlas*m_pShowScore;
	LabelAtlas*m_pBulletLabel;

	PanelLayerDelegate*m_pDelegate;
public:
	PanelLayer();
	~PanelLayer();
	CREATE_FUNC(PanelLayer);
	bool init();

	virtual void update(float dt);

	void setDelegate(PanelLayerDelegate*pDelegate);
private:
	void gamePause(Ref*);//ÔÝÍ££¬µ÷ÓÃGameScene::pause
};
#endif