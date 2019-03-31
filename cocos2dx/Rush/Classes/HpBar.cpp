#include "HpBar.h"
HpBar::HpBar():m_pHpBarBG(nullptr),m_pHpBar(nullptr)
	,m_fMaxValue(0),m_fCurValue(0)
{
}
HpBar::~HpBar()
{
}
HpBar*HpBar::create(std::string textureName,std::string textureBGName,float maxValue)
{
	HpBar*pHpBar = new HpBar();
	if(pHpBar && pHpBar->init(textureName,textureBGName,maxValue))
		pHpBar->autorelease();
	else
		CC_SAFE_DELETE(pHpBar);
	return pHpBar;
}
bool HpBar::init(std::string textureName,std::string textureBGName,float maxValue)
{
	if(!Node::init())
		return false;
	bool bRet = false;
	do
	{
		m_fMaxValue = m_fCurValue = maxValue;
		//create loadingbar
		m_pHpBar = cocos2d::ui::LoadingBar::create(textureName,100);
		//set the content size
		cocos2d::Size size = m_pHpBar->getContentSize();
		if(textureBGName != "")
		{
			m_pHpBarBG = cocos2d::Sprite::create(textureBGName);
			this->addChild(m_pHpBarBG);
			m_pHpBarBG->setPosition(cocos2d::ccp(size.width/2,size.height/2));
		}
		this->addChild(m_pHpBar);
		this->setContentSize(size);
		m_pHpBar->setPosition(cocos2d::ccp(size.width/2,size.height/2));
		setAnchorPoint(cocos2d::ccp(0.5,0.5));
		bRet = true;
	}while(0);
	return bRet;
}
void HpBar::setValue(float curValue)
{
	if(m_pHpBar != nullptr && curValue < m_fMaxValue)
	{
		m_fCurValue = curValue;
		m_pHpBar->setPercent(curValue/m_fMaxValue * 100);
	}
}
float HpBar::getValue() const
{
	return m_pHpBar == nullptr?0:m_fCurValue;
}