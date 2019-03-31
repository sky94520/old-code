#include "PanelLayer.h"
#include "DynamicData.h"
#include "Shovel.h"

PanelLayer::PanelLayer()
	:m_pSunLabel(nullptr),m_pSunBg(nullptr)
	,m_pShovelBg(nullptr),m_pShovel(nullptr)
{
}

PanelLayer::~PanelLayer()
{
}

bool PanelLayer::init()
{
	//加载外部关卡 todo
	auto node = ui::UIWidgetManager::getInstance()->createWidgetsWithXml("scene/PanelLayer.xml");
	this->addChild(node);
	//获取相关信息
	m_pSunLabel = node->getChildByName<LabelAtlas*>("sun_label");
	m_pSunBg = node->getChildByName<Sprite*>("sun_bg");
	m_pShovelBg = node->getChildByName<Sprite*>("shovel_bg");
	//初始化铲子
	m_pShovel = Shovel::create();
	m_pShovel->setPosition(m_pShovelBg->getPosition());

	this->addChild(m_pShovel);

	return true;
}

void PanelLayer::updateUI()
{
	this->updateSun();
}

void PanelLayer::updateSun()
{
	//获取阳光数目
	auto sunNumber = DynamicData::getInstance()->getSunNumber();
	auto sNum = StringUtils::toString(sunNumber);

	m_pSunLabel->setString(sNum);
}

Point PanelLayer::getSunBgPosition()
{
	return m_pSunBg->getPosition();
}

void PanelLayer::seletcShovel()
{
	m_pShovel->selected();
}

void PanelLayer::unselectShovel()
{
	if (m_pShovel->isSelected())
	{
		m_pShovel->unselected();
	}
}

bool PanelLayer::isClickShovel(const Point&pos)const
{
	auto rect = m_pShovel->getBoundingBox();

	if (rect.containsPoint(pos))
		return true;
	return false;
}

bool PanelLayer::isSelectedShovel()
{
	return m_pShovel->isSelected();
}