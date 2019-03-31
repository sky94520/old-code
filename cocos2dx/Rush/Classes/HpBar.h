#ifndef __HpBar_H__
#define _HpBar_H__
#include "cocos2d.h"
#include "ui/CocosGUI.h"
class HpBar : public cocos2d::Node
{
private:
	cocos2d::Sprite*m_pHpBarBG;
	cocos2d::ui::LoadingBar*m_pHpBar;
	float m_fMaxValue;
	float m_fCurValue;
	HpBar();
	~HpBar();
public:
	static HpBar*create(std::string textureName,std::string textureBGName = "",float maxValue=100);
	bool init(std::string textureName,std::string textureBGName,float maxValue);
	//value from 1 to 100
	void setValue(float curValue);
	float getValue() const;
};
#endif