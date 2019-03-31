#include "GoldTimer.h"
#include "FishingJoyData.h"
GoldTimer::GoldTimer()
	:m_nGold(5),m_nSecond(60),m_elpased(0.f),m_pLabel(nullptr)
{
}
GoldTimer::~GoldTimer()
{
}
bool GoldTimer::init()
{
	m_pLabel = LabelAtlas::create("60","common-font.png",16,24,'0');
	this->addChild(m_pLabel);
	setContentSize(m_pLabel->getContentSize());
	return true;
}
void GoldTimer::update(float dt)
{
	m_elpased += dt;
	if(m_elpased >= m_nSecond)
	{
		m_elpased -= m_nSecond;
		auto pos = this->getWorldPosition();
		auto size = this->getContentSize();
		std::string text = StringUtils::format("%d %.0f %.0f",m_nGold,pos.x+size.width/2,pos.y+size.height/2);
		Value value = Value(text);
		FishingJoyData::getInstance()->alterGold(value,true);
	}
	int second = m_nSecond - m_elpased;
	//Value(second).asString()
	m_pLabel->setString(StringUtils::format("%d",second));
}