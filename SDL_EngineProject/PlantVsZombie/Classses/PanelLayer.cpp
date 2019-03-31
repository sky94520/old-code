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
	//�����ⲿ�ؿ� todo
	auto node = ui::UIWidgetManager::getInstance()->createWidgetsWithXml("scene/PanelLayer.xml");
	this->addChild(node);
	//��ȡ�����Ϣ
	m_pSunLabel = node->getChildByName<LabelAtlas*>("sun_label");
	m_pSunBg = node->getChildByName<Sprite*>("sun_bg");
	m_pShovelBg = node->getChildByName<Sprite*>("shovel_bg");
	//��ʼ������
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
	//��ȡ������Ŀ
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