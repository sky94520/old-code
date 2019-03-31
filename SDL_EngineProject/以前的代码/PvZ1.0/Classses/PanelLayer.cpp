#include "PanelLayer.h"
#include "DynamicData.h"
#include "Shovel.h"
PanelLayer::PanelLayer()
	:m_pSunBackground(nullptr),m_pSunNumLabel(nullptr)
	,m_pShovel(nullptr)
{
}
PanelLayer::~PanelLayer()
{
	NotificationCenter::getInstance()->removeObserver(this,"sunshine");
}
bool PanelLayer::init()
{
	//����̫����
	m_pSunBackground = Sprite::create("Resources/SunBack.png");
	//sunBack->setScale(1.5,1.5);
	m_pSunBackground->setPositionX(100);
	this->addChild(m_pSunBackground);
	//̫������
	m_pSunNumLabel = LabelAtlas::create("050","Resources/LabelAtlas.png",21,21,'0');
	m_pSunNumLabel->setPosition(50,5);
	m_pSunBackground->addChild(m_pSunNumLabel);
	//���̫�������۲���
	NotificationCenter::getInstance()->addObserver(this,scheduleO_selector(PanelLayer::updateSunNum),"sunshine");
	//����
	m_pShovel = Shovel::create();
	m_pShovel->setPosition(400,0);
	this->addChild(m_pShovel);
	//ˢ��̫������
	this->updateSunNum(this);
	return true;
}
bool PanelLayer::isClickedShovel(const Point&pos)const
{
	//��ȡ��������
	auto worldPos = m_pShovel->getWorldPosition();
	Rect rect = Rect(worldPos,m_pShovel->getContentSize());
	//����˲���
	if(rect.containsPoint(pos))
	{
		//������δѡ��
		if(m_pShovel->isSelected() == false)
		{
			m_pShovel->setSelected(true);
			m_pShovel->runBlinkAction();//������˸����
		}
		else
		{
			m_pShovel->setSelected(false);
			m_pShovel->clear();//�ָ�ԭ������
		}
		return true;
	}
	return false;
}
Shovel* PanelLayer::getShovel()const
{
	return m_pShovel;
}
void PanelLayer::updateSunNum(Object*)
{
	auto sunNum = DynamicData::getInstance()->getSunNumber();
	auto text = StringUtils::format("%03d",sunNum);
	m_pSunNumLabel->setString(text);
}