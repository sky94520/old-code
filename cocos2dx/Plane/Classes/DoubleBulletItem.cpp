#include "DoubleBulletItem.h"
#include "StaticData.h"
#include "SystemHeader.h"
DoubleBulletItem::DoubleBulletItem()
	:m_intervalTime(0),m_elapsed(0.f),m_bInvalid(true)
{
}
DoubleBulletItem::~DoubleBulletItem()
{
}
bool DoubleBulletItem::init()
{
	bindSprite(Sprite::createWithSpriteFrameName("DoubleBulletItem.png"));
	//ÿn�����һ��
	m_intervalTime = StaticData::getInstance()->getValueForKey("DoubleBulletItemIntervalTime").asFloat();
	m_duration = StaticData::getInstance()->getValueForKey("DoubleBulletDuration").asFloat();
	setHitPoints(1);
	setCurHP(0);
	m_speed = 50;

	setVisible(false);
	return true;
}
void DoubleBulletItem::onHurt()
{
}
void DoubleBulletItem::onDead()
{
	setVisible(false);
	this->stopAllActions();
	this->getSprite()->stopAllActions();
	//���ݸ�BulletLayer
	BulletType type = BulletType::kBulletType_double;
	NotificationCenter::getInstance()->postNotification("change bullet",(Ref*)&type);
	//ʹ�ӵ���ԭ
	m_bInvalid = false;
}
