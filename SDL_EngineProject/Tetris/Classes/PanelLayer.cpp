#include "PanelLayer.h"
#include "DynamicData.h"

PanelLayer::PanelLayer()
	:m_pScore(nullptr),m_pLevel(nullptr)
{
}
PanelLayer::~PanelLayer()
{
}
bool PanelLayer::init()
{
	m_pScore = LabelAtlas::createWithColorKey("score:0","lazyfont.png",39,55,Color(0,255,255),0);
	m_pScore->setFontKerning(0.4f);
	m_pScore->setPosition(280,100);
	m_pScore->setAnchorPoint(Point::ZERO);
	this->addChild(m_pScore);

	m_pLevel = LabelAtlas::createWithColorKey("level:0","lazyfont.png",39,55,Color(0,255,255),0);
	m_pLevel->setFontKerning(0.4f);
	m_pLevel->setAnchorPoint(Point::ZERO);
	m_pLevel->setPosition(280,200);
	this->addChild(m_pLevel);

	NotificationCenter::getInstance()->addObserver(this,scheduleO_selector(PanelLayer::updateSelf),"DynamicData");
	
	return true;
}
void PanelLayer::updateSelf(Object*sender)
{
	int score = DynamicData::getInstance()->getScore();
	int level = DynamicData::getInstance()->getLevel();

	m_pScore->setString(StringUtils::format("score:%d",score));
	m_pLevel->setString(StringUtils::format("level:%d",level));
}