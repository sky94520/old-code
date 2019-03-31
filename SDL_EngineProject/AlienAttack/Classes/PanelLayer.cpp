#include "PanelLayer.h"
#include "DynamicData.h"

PanelLayer::PanelLayer()
	:m_pLives(nullptr),m_pGold(nullptr)
{
}
PanelLayer::~PanelLayer()
{
	NotificationCenter::getInstance()->removeObserver(this,"dynamic data");
}
bool PanelLayer::init()
{
	//����ui���
	auto node = ui::UIWidgetManager::getInstance()->createWidgetsWithXml("scene/PanelLayer.xml");
	this->addChild(node);

	m_pLives = node->getChildByName<LabelAtlas*>("lives");
	m_pGold = node->getChildByName<LabelAtlas*>("gold");
	//��ӹ۲���
	NotificationCenter::getInstance()->addObserver(this,scheduleO_selector(PanelLayer::updateSelf),"dynamic data");
	//ˢ��һ���Լ�
	//this->updateSelf(this);
	return true;
}
void PanelLayer::updateSelf(Object*sender)
{
	int lives = DynamicData::getInstance()->getPlayerLives();
	m_pLives->setString(to_string(lives));

	int gold = DynamicData::getInstance()->getGold();
	m_pGold->setString(to_string(gold));
}