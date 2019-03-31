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
	//增加太阳槽
	m_pSunBackground = Sprite::create("Resources/SunBack.png");
	//sunBack->setScale(1.5,1.5);
	m_pSunBackground->setPositionX(100);
	this->addChild(m_pSunBackground);
	//太阳数量
	m_pSunNumLabel = LabelAtlas::create("050","Resources/LabelAtlas.png",21,21,'0');
	m_pSunNumLabel->setPosition(50,5);
	m_pSunBackground->addChild(m_pSunNumLabel);
	//添加太阳数量观察者
	NotificationCenter::getInstance()->addObserver(this,scheduleO_selector(PanelLayer::updateSunNum),"sunshine");
	//铲子
	m_pShovel = Shovel::create();
	m_pShovel->setPosition(400,0);
	this->addChild(m_pShovel);
	//刷新太阳数量
	this->updateSunNum(this);
	return true;
}
bool PanelLayer::isClickedShovel(const Point&pos)const
{
	//获取世界坐标
	auto worldPos = m_pShovel->getWorldPosition();
	Rect rect = Rect(worldPos,m_pShovel->getContentSize());
	//点击了铲子
	if(rect.containsPoint(pos))
	{
		//若铲子未选中
		if(m_pShovel->isSelected() == false)
		{
			m_pShovel->setSelected(true);
			m_pShovel->runBlinkAction();//运行闪烁动画
		}
		else
		{
			m_pShovel->setSelected(false);
			m_pShovel->clear();//恢复原来动画
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