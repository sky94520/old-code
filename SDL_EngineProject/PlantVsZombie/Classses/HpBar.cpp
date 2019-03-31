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
		pHpBar->autorelease();
	else
		SDL_SAFE_DELETE(pHpBar);

	return pHpBar;
}

bool HpBar::init(std::string textureName,std::string textureBGName,float maxValue)
{
	if(!Node::init())
		return false;

	m_fMaxValue = m_fCurValue = maxValue;
	//create loadingbar
	m_pHpBar = ProgressTimer::create(Sprite::create(textureName));
	m_pHpBar->setType(ProgressTimer::Type::BAR);
	m_pHpBar->setBarChangeRate(Point(1.f,0.f));
	m_pHpBar->setMidpoint(Point(1.f,0.f));
	//set the position
	Size size = m_pHpBar->getContentSize();

	m_pHpBar->setPercentage(100.f);
	if(textureBGName != "")
	{
		m_pHpBarBG = Sprite::create(textureBGName);
		this->addChild(m_pHpBarBG,-1);
		//m_pHpBarBG->setPosition(Point(size.width/2,size.height/2));
	}
	this->addChild(m_pHpBar);
	this->setContentSize(size);
	this->setAnchorPoint(Point(0.5f,0.5f));

	return true;
}

void HpBar::setValue(float curValue)
{
	if(m_pHpBar != nullptr && curValue < m_fMaxValue)
	{
		m_fCurValue = curValue;
		auto percentage = curValue/m_fMaxValue * 100.f;
		m_pHpBar->setPercentage(percentage);
	}
}

float HpBar::getValue() const
{
	return m_pHpBar == nullptr?0.f:m_fCurValue;
}