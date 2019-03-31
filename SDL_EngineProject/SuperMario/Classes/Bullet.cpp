#include "Bullet.h"
#include "MoveBehavior.h"
const int Bullet::BULLET_ANIMATION_TAG = 1;

Bullet::Bullet()
	:m_type(BulletType::None)
{
}
Bullet::~Bullet()
{
}
void Bullet::reset()
{
}
//--------------------MarioBullet------------------------------
MarioBullet::MarioBullet()
	:m_curHeight(0.f),m_maxHeight(0.f)
{
}
MarioBullet::~MarioBullet()
{
}

bool MarioBullet::init()
{
	//绑定贴图
	this->bindSprite(Sprite::createWithSpriteFrameName("mario_bullet.png"));

	this->setBulletType(BulletType::Mario);

	return true;
}
void MarioBullet::setCustomName(const string&customName)
{
	m_customName = customName;
}
void MarioBullet::performMove(float dt)
{
	if(m_pMoveBehavior)
	{
		m_pMoveBehavior->performMove(this,dt);
		auto velocity = this->getVelocity();

		if(m_curHeight > m_maxHeight)
		{
			m_curHeight = 0.f;
			this->setVelocity(Point(velocity.x,-velocity.y));
		}
		else if(velocity.y < 0.f)
		{
			m_curHeight += SDL_fabs(velocity.y);
		}
	}
}
bool MarioBullet::onHurt(int damage)
{
	return true;
}
void MarioBullet::onDead()
{
	this->getSprite()->stopActionByTag(BULLET_ANIMATION_TAG);
	this->stopAllActions();
	//播放完死亡动画后直接死亡
	auto animate = Entity::createAnimate("mario_bullet_d%02d.png",0,2,0.05f,1);
	animate->setTag(BULLET_ANIMATION_TAG);

	DelayTime*delayTime = DelayTime::create(animate->getDuration());
	CallFunc*end = CallFunc::create([this](){
		this->setDead(true);
		//发送死亡消息
		_eventDispatcher->dispatchCustomEvent(m_customName);
	});
	//运行动画和动作
	this->runAction(Sequence::create(delayTime,end,NULL));
	this->getSprite()->runAction(animate);
}
bool MarioBullet::tileCollidedX(bool bRight)
{
	//碰到墙壁，直接死亡
	this->hurt(this->getCurHp());
	//碰到墙壁音效
	//SoundManager::getInstance()->playEffect("sound/mario_bullet_tile_collided.ogg",0);

	return true;
}
bool MarioBullet::tileCollidedY(bool bDown)
{
	m_curHeight = 0.f;
	return false;
}
void MarioBullet::runNormalAnimation()
{
	//对当前的一帧进行旋转
	RotateBy*rotate = RotateBy::create(0.2f,360.f);
	RepeatForever*r = RepeatForever::create(rotate);
	r->setTag(BULLET_ANIMATION_TAG);

	this->getSprite()->runAction(r);
}
void MarioBullet::reset()
{
	this->setDead(false);
	this->setVelocity(Point::ZERO);
	this->setCurHp(this->getMaxHp());
	m_curHeight = 0.f;
}