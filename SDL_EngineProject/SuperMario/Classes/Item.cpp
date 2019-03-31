#include "Item.h"
#include "MoveBehavior.h"
#include "EffectBehavior.h"

Item::Item()
	:m_pEffectBehavior(nullptr),m_bUpdate(true)
{
}
Item::~Item()
{
}
bool Item::init()
{
	return true;
}
void Item::performEffect(Player*player)
{
	if(m_pEffectBehavior)
	{
		m_pEffectBehavior->performEffect(this,player);
	}
}
void Item::performMove(float dt)
{
	BehaviorEntity::performMove(dt);
}
void Item::setEffectBehavior(EffectBehavior*effectBehavior)
{
	m_pEffectBehavior = effectBehavior;
}
void Item::runNormalAnimation()
{
}
void Item::onDead()
{
	m_bDead = true;
}
void Item::reset()
{
	//重置行为
	m_pMoveBehavior = nullptr;
	m_pEffectBehavior = nullptr;

	this->stopAllActions();
	this->getSprite()->stopAllActions();
}
bool Item::tileCollidedX(bool bRight)
{
	return false;
}
bool Item::tileCollidedY(bool bDown)
{
	return true;
}
Rect Item::getCollisionBoundingBox()const
{
	auto r = Entity::getCollisionBoundingBox();
	//根据类型对包围盒进行微调整
	if(m_type == kItemType_Mushroom)
	{
		r.size.height -= 2;
	}
	return r;
}
//----------------------------------星星----------------------------
Star::Star()
	:m_curJumpHeight(0.f)
	,MAX_JUMP_HEIGHT(Director::getInstance()->getVisibleSize().height/8)
{
}
Star::~Star()
{
}
bool Star::init()
{
	//绑定精灵
	this->bindSprite(Sprite::createWithSpriteFrameName("item4_00.png"));
	//运行动画
	Animate*animate = Entity::createAnimate("item4_%02d.png",0,3,0.4f);
	this->getSprite()->runAction(animate);

	return true;
}
void Star::reset()
{
	m_curJumpHeight = 0.f;
}
void Star::performMove(float dt)
{
	if(m_pMoveBehavior)
	{
		m_pMoveBehavior->performMove(this,dt);
		auto velocity = this->getVelocity();

		if(m_curJumpHeight > MAX_JUMP_HEIGHT)
		{
			m_curJumpHeight = 0.f;
			this->setVelocity(Point(velocity.x,-velocity.y));
		}
		else if(velocity.y < 0.f)
		{
			m_curJumpHeight += SDL_fabs(velocity.y);
		}
	}
}
bool Star::tileCollidedX(bool bRight)
{
	m_curJumpHeight = 0.f;
	return false;
}
bool Star::tileCollidedY(bool bDown)
{
	m_curJumpHeight = 0.f;

	//auto velocity = this->getVelocity();
	//this->setVelocity(Point(velocity.x,-velocity.y));
	return false;
}
//-----------------------------TileCoin------------------------------
TileCoin::TileCoin()
	:m_nCoinCount(0),m_elpased(0.f)
	,m_pObject(nullptr)
{
}
TileCoin::~TileCoin()
{
}
bool TileCoin::init()
{
/*	this->bindSprite(Sprite::createWithSpriteFrameName("gold00.png"));
	//重新设置大小为0
	this->setContentSize();*/
	return true;
}
void TileCoin::associateWithTMXObject(TMXObject*object)
{
	m_pObject = object;
	//设置金币的数目
	auto properties = object->getProperties();
	if(properties.empty())
		m_nCoinCount = 1;
	else
		m_nCoinCount = rand()%5+2;
}
bool TileCoin::onHurt(int damage)
{
	if(m_nCoinCount == 1)
		return true;

	m_nCoinCount --;
	return false;
}
void TileCoin::reset()
{
}
void TileCoin::performMove(float dt)
{
	//金币的数量最低是1
	if(m_nCoinCount == 1)
		return;
	//金币的数目会随着时间而流逝,直到只剩下一个
	m_elpased += dt;
	if(m_elpased > 2.f)
	{
		m_elpased -= 2.f;
		m_nCoinCount--;
	}
}