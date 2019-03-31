#ifndef __SettingLayer_H__
#define __SettingLayer_H__
#include "BaseLayer.h"
USING_NS_CC;
class SettingLayer:public BaseLayer
{
private:
	bool m_bMusicPlaying;
	bool m_bEffectPlaying;
public:
	SettingLayer();
	CREATE_FUNC(SettingLayer);
	bool init();
	static Scene*createScene();
protected:
	virtual void menuBackCallback(Ref*);
	void musicToggle(Ref*);
	void effectToggle(Ref*);
};
#endif