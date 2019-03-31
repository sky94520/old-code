#include "ItemLayer.h"
#include "DoubleBulletItem.h"
#include "GameLayer.h"
#include "StaticData.h"
#include "DynamicData.h"
ItemLayer::ItemLayer()
{
}
ItemLayer::~ItemLayer()
{
}
ItemLayer*ItemLayer::create(GameLayerDelegate*pDelegate)
{
	auto layer = new ItemLayer();
	if(layer && layer->init(pDelegate))
		layer->autorelease();
	else
		CC_SAFE_DELETE(layer);
	return layer;
}
bool ItemLayer::init(GameLayerDelegate*pDelegate)
{
	const int PTM_RATIO = StaticData::getInstance()->getValueForKey("PTM_RATIO").asInt();
	//添加双发子弹道具
	m_pDoubleBulletItem = DoubleBulletItem::create();
	this->addChild(m_pDoubleBulletItem);
	//添加物理体积
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	pDelegate->bindPhysicalBody(m_pDoubleBulletItem,"DoubleBulletItem",&bodyDef);
	return true;
}
void ItemLayer::showBulletItem()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//重置
	this->setVisible(true);
	//位置
	Size size = m_pDoubleBulletItem->getContentSize();
	float x = CCRANDOM_0_1()*visibleSize.width;
	float y = visibleSize.height + size.height/2;
	Vec2 endPos = Vec2(0,-visibleSize.height - size.height);

	MoveBy*move = MoveBy::create(endPos.length()/m_pDoubleBulletItem->getSpeed(),endPos);
	RotateTo*rotate1 = RotateTo::create(1.f,30);
	RotateTo*rotate2 = RotateTo::create(1.f,-30);
	RepeatForever *repeat = RepeatForever::create(Sequence::createWithTwoActions(rotate1,rotate2));
	
	CallFunc*deadCallback = CallFunc::create([&](){
		m_pDoubleBulletItem->setCurHP(0);
		m_pDoubleBulletItem->setVisible(false);
		m_pDoubleBulletItem->getSprite()->stopAllActions();
	});
	//set
	m_pDoubleBulletItem->setRotation(0);
	m_pDoubleBulletItem->setPosition(x,y);
	m_pDoubleBulletItem->setCurHP(m_pDoubleBulletItem->getHitPoints());
	m_pDoubleBulletItem->setVisible(true);
	m_pDoubleBulletItem->runAction(Sequence::createWithTwoActions(move,deadCallback));
	m_pDoubleBulletItem->getSprite()->runAction(repeat);
}
void ItemLayer::update(float dt)
{
	auto item = m_pDoubleBulletItem;
	//只有在吃掉或到达目的地时，才重新计时
	if(!item->isAlive() && !item->isVisible())
	{
		auto elapsed = item->getElapsed() + dt;
		if(item->isInvalid() == false)
			DynamicData::getInstance()->setBulletDuration(item->getDuration() - elapsed);
		//道具失效
		if(item->isInvalid() == false&& elapsed >= item->getDuration())
		{
			item->setInvalid(true);
			BulletType type = BulletType::kBulletType_normal;
			NotificationCenter::getInstance()->postNotification("change bullet",(Ref*)&type);
		}
		if(elapsed >= item->getIntervalTime())
		{
			elapsed = 0.f;
			showBulletItem();
		}
		item->setElapsed(elapsed);
	}
}