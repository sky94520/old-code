#include "ChooseBulletLayer.h"
#include "BulletCard.h"
#include "ChooseBulletChildLayer.h"
ChooseBulletLayer::ChooseBulletLayer()
	:m_pSelectedItem(nullptr),m_pChildLayer(nullptr)
	,m_pCurrentItem(nullptr),m_pDelegate(nullptr)
{
}
ChooseBulletLayer::~ChooseBulletLayer()
{
}
bool ChooseBulletLayer::init()
{
	m_pChildLayer = ChooseBulletChildLayer::create();
	m_pChildLayer->setPosition(390,280);
	m_pChildLayer->setVisible(false);
	this->addChild(m_pChildLayer);
	//���õ�ǰѡ��
	m_pSelectedItem = m_pChildLayer->getItemByType(BulletType::kBulletType_1);
	m_pCurrentItem = m_pSelectedItem->clone(); 
	m_pCurrentItem->setPosition(390,285 + m_pCurrentItem->getContentSize().height);
	this->addChild(m_pCurrentItem);
	return true;
}
void ChooseBulletLayer::chooseBullet(const Point&pos)
{
	//���������ӵ����ж��ӳ����Ƿ��Ѿ���ʾ
	Rect rect = m_pCurrentItem->getBoundingBox();
	if(rect.containsPoint(pos))
	{
		ToggleVisibility*toggleAction = ToggleVisibility::create();
		m_pChildLayer->runAction(toggleAction);
		return ;
	}
	//����ӳ����ɼ������´���
	if(m_pChildLayer->isVisible())
	{
		auto selectedItem = m_pChildLayer->getSelectedItem(pos);
		if(selectedItem == nullptr)
			return;
		if(selectedItem == m_pSelectedItem)
		{
			m_pChildLayer->setVisible(false);
			return;
		}
		m_pChildLayer->setVisible(false);
		m_pSelectedItem = selectedItem;
		//�Ƴ�
		m_pCurrentItem->removeFromParent();
		m_pCurrentItem = m_pSelectedItem->clone();
		m_pCurrentItem->setPosition(390,285 + m_pCurrentItem->getContentSize().height);
		this->addChild(m_pCurrentItem);
		//�����ӵ�����
		m_pDelegate->setBulletType(m_pCurrentItem->getType());
	}
}
bool ChooseBulletLayer::subBulletCount()
{
	m_pSelectedItem->subBulletCount();
	return m_pCurrentItem->subBulletCount();
}
void ChooseBulletLayer::setDelegate(ChooseBulletDelegate*pDelegate)
{
	m_pDelegate = pDelegate;
}