#include "BulletLayer.h"
#include "Bullet.h"
#include "StaticData.h"
BulletLayer::BulletLayer()
	:m_pDelegate(nullptr),m_bulletType(BulletType::kBulletType_normal)
{
}
BulletLayer::~BulletLayer()
{
	NotificationCenter::getInstance()->removeObserver(this,"change bullet");
}
bool BulletLayer::init()
{
	//添加观察者
	NotificationCenter::getInstance()->addObserver(this,
		CC_CALLFUNCO_SELECTOR(BulletLayer::setBulletType),"change bullet",nullptr);
	return true;
}
void BulletLayer::shootTo(const Vec2&startPos)
{
	if(m_bulletType == BulletType::kBulletType_normal)
		shoot(startPos+Vec2(0,20));
	else if(m_bulletType == BulletType::kBulletType_double)
	{
		Vec2 pos = Vec2(20,0);
		shoot(startPos - pos);
		shoot(startPos + pos);
	}
}
void BulletLayer::shoot(const Point&startPos)
{
	const int PTM_RATIO = StaticData::getInstance()->getValueForKey("PTM_RATIO").asInt();
	Bullet*bullet = nullptr;
	for(int i=0;i<m_bulletList.size();i++)
	{
		auto item = m_bulletList.at(i);
		if(item->isAlive() == false && !item->isVisible())
		{
			bullet = item;
			break;
		}
	}
	if(bullet == nullptr)
	{
		bullet = Bullet::create();
		this->addChild(bullet);
		m_bulletList.push_back(bullet);
		//添加物理
		MyBody myBody;
		myBody.type = b2_dynamicBody;
		myBody.position = b2Vec2(startPos.x/PTM_RATIO,startPos.y/PTM_RATIO);
		myBody.density = 0.1f;
		myBody.firction = 0.2f;
		myBody.categoryBits = 0x04;
		myBody.maskBits = 0x01;
		//形状
		b2PolygonShape*shape = new b2PolygonShape();
		shape->SetAsBox(bullet->getContentSize().width/PTM_RATIO/2,bullet->getContentSize().height/PTM_RATIO/2);
		m_pDelegate->bindPhysicalBody(bullet,myBody,shape);
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 endPos = Vec2(0,visibleSize.height + bullet->getContentSize().height/2);
	
	bullet->setCurHP(bullet->getHitPoints());
	bullet->setVisible(true);
	bullet->setPosition(startPos);

	MoveBy*move = MoveBy::create(endPos.length()/bullet->getSpeed(),endPos);
	CallFunc*callfunc = CallFunc::create([bullet](){
		bullet->setVisible(false);
		bullet->setCurHP(0);
	});
	bullet->runAction(Sequence::createWithTwoActions(move,callfunc));
}
void BulletLayer::setBulletType(Ref*sender)
{
	BulletType*type = (BulletType*)sender;
	log("%d",type);
	m_bulletType = *type;
}
void BulletLayer::setDelegate(BulletLayerDelegate*pDelegate)
{
	m_pDelegate = pDelegate;
}