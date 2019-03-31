#include "HpBar.h"
HpBar::HpBar():
	m_pHpBarBG(nullptr),m_pHpBar(nullptr)
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
		pHpBar->autoRelease();
	else
		SDL_SAFE_DELETE(pHpBar);
	return pHpBar;
}
bool HpBar::init(std::string textureName,std::string textureBGName,float maxValue)
{
	if(!Node::init())
		return false;
	bool bRet = false;
	m_fMaxValue = m_fCurValue = maxValue;
	//create loadingbar
	m_pHpBar = LoadingBar::create(textureName,1.f);
	//set the content size
	Size size = m_pHpBar->getContentSize();
	if(textureBGName != "")
	{
		m_pHpBarBG = Sprite::create(textureBGName);
		this->addChild(m_pHpBarBG);
		//m_pHpBarBG->setPosition(Point(size.width/2,size.height/2));
	}
	this->addChild(m_pHpBar);
	this->setContentSize(size);
	bRet = true;
	return bRet;
}
void HpBar::setValue(float curValue)
{
	if(m_pHpBar != nullptr && curValue < m_fMaxValue)
	{
		m_fCurValue = curValue;
		m_pHpBar->setPercent(curValue/m_fMaxValue);
	}
}
float HpBar::getValue() const
{
	return m_pHpBar == nullptr?0:m_fCurValue;
}