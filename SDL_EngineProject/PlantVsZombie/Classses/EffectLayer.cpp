#include "EffectLayer.h"
#include "NameDef.h"

bool EffectLayer::init()
{
	return true;
}

void EffectLayer::showZombieDie(Layer*layer,const string& zombieName,const Point&pos,int localZOrder,bool flipX)
{
	string animationName = "ZombieDie";

	if (zombieName == PAPERZOMBIE_NAME || zombieName == POLEVAULTINGZOMBIE_NAME
		|| zombieName == BACKUP_ZOMBIE_NAME || zombieName == DANCING_ZOMBIE_NAME)
	{
		animationName = StringUtils::format("%sDie",zombieName.c_str());
	}

	auto sprite = this->runEffectWithAnimationName(animationName,pos,layer,localZOrder);
	sprite->setFlipX(flipX);
}

void EffectLayer::showZombieBoom(Layer*layer,const string& zombieName,const Point&pos,int localZOrder,bool flipX)
{
	auto animationName = "BoomDie";

	auto sprite = this->runEffectWithAnimationName(animationName,pos,layer,localZOrder);
	sprite->setFlipX(flipX);
}

void EffectLayer::showZombieHead(Layer*layer,const string& zombieName,const Point&pos,int localZOrder,bool flipX)
{
	string animationName = "ZombieHead";

	if (zombieName == PAPERZOMBIE_NAME || zombieName == POLEVAULTINGZOMBIE_NAME
		|| zombieName == BACKUP_ZOMBIE_NAME || zombieName == DANCING_ZOMBIE_NAME)
	{
		animationName = StringUtils::format("%sHead",zombieName.c_str());
	}
	auto sprite = this->runEffectWithAnimationName(animationName,pos,layer,localZOrder);
	//sprite->setFlipX(flipX);
}

void EffectLayer::showGarnishryFallAction(Layer*layer,const string&spriteName,const Point&pos,int localZOrder,bool flipX)
{
	float duration = 0.6f;
	float rotation = 20.f;

	auto sprite = this->runEffectWithRotate(spriteName,duration);

	sprite->setPosition(pos);
	sprite->setRotation(rotation);

	layer->addChild(sprite,localZOrder);
}


void EffectLayer::showRisingDirt(const Point&pos,Layer*layer,int localZOrder)
{
	auto animationName = "RisingDirt";
	
	this->runEffectWithAnimationName(animationName,pos,layer,localZOrder);
}

void EffectLayer::showExplosionSpudow(const Point&pos,Layer*layer,int localZOrder)
{
	//展示炸死动画
	auto animationName = "PotatoMineMashed";
	this->runEffectWithAnimationName(animationName,pos,layer,localZOrder);

	animationName = "ExplosionSpudow";
	this->runEffectWithAnimationName(animationName,pos,layer,localZOrder);
}

void EffectLayer::addButterSplat(const Point&pos,Layer*layer,int localZOrder,int uniqueID)
{
	Sprite*sprite = Sprite::createWithSpriteFrameName("Cornpult_butter_splat.png");

	sprite->setPosition(pos);
	sprite->setTag(uniqueID);

	layer->addChild(sprite,localZOrder);
}

void EffectLayer::removeButterSplat(Layer*layer,int uniqueID)
{
	auto child = layer->getChildByTag(uniqueID);
	
	if (child != nullptr)
	{
		child->removeFromParent();
	}
}

void EffectLayer::addIceTrap(const Point&pos,Layer*layer,int localZOrder,int uniqueID)
{
	Sprite*sprite = Sprite::createWithSpriteFrameName("icetrap.png");

	sprite->setPosition(pos);
	sprite->setTag(uniqueID);

	layer->addChild(sprite,localZOrder);
}
void EffectLayer::removeIceTrap(Layer*layer,int uniqueID)
{
	this->removeButterSplat(layer,uniqueID);
}

void EffectLayer::addGarnishryEffect(int uniqueID,const Point&pos,const string&str,Layer*layer,int localZOrder)
{
	Sprite*sprite = Sprite::create(str);

	sprite->setPosition(pos);
	sprite->setTag(uniqueID);

	layer->addChild(sprite,localZOrder);
}

void EffectLayer::removeGarnishryEffect(Layer*layer,int uniqueID)
{
	this->removeButterSplat(layer,uniqueID);
}

float EffectLayer::showCoffeeBeanEatAction(const Point&pos,Layer*layer,int localZOrder)
{
	auto animationName = "CoffeeBeanEat";
	//获取动画
	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	auto firstFrame = animation->getFrames().front()->getSpriteFrame();

	Sprite*sprite = Sprite::createWithSpriteFrame(firstFrame);
	sprite->setPosition(pos);

	layer->addChild(sprite,localZOrder);
	//运行动画
	Animate*animate = Animate::create(animation);
	RemoveSelf*remove = RemoveSelf::create();

	auto seq = Sequence::createWithTwoActions(animate,remove);
	sprite->runAction(seq);

	return animate->getDuration();

}

void EffectLayer::showSnow(const Point&pos,Layer*layer,int localZOrder)
{
	Sprite*sprite = Sprite::create("sprite/Snow.png");
	sprite->setPosition(pos);

	layer->addChild(sprite,localZOrder);

	DelayTime*delayTime = DelayTime::create(0.3f);
	RemoveSelf*remove = RemoveSelf::create();

	auto seq = Sequence::createWithTwoActions(delayTime,remove);

	sprite->runAction(seq);
}

void EffectLayer::showBoom(const Point&pos,Layer*layer,int localZOrder)
{
	auto animationName = "Boom";
	
	auto sprite = this->runEffectWithAnimationName(animationName,pos,layer,localZOrder);

	sprite->setAnchorPoint(Point(0.5f,1.f));
}

void EffectLayer::showFire(const Point&pos,Layer*layer,int localZOrder)
{
	auto animationName = "FirePeaBulletHit";
	
	auto sprite = this->runEffectWithAnimationName(animationName,pos,layer,localZOrder,Point(0.5f,1.f));

}

Sprite*EffectLayer::runEffectWithAnimationName(const string&animationName
	,const Point&pos,Layer*layer,int tag,const Point&anchorPoint)
{
	//获取动画
	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	auto firstFrame = animation->getFrames().front()->getSpriteFrame();

	Sprite*sprite = Sprite::createWithSpriteFrame(firstFrame);
	sprite->setPosition(pos);
	sprite->setAnchorPoint(anchorPoint);

	layer->addChild(sprite,tag);
	//运行动画
	Animate*animate = Animate::create(animation);
	RemoveSelf*remove = RemoveSelf::create();

	auto seq = Sequence::createWithTwoActions(animate,remove);
	sprite->runAction(seq);

	return sprite;
}

Sprite*EffectLayer::runEffectWithRotate(const string&spriteName,float duration)
{
	Sprite*sprite = Sprite::createWithSpriteFrameName(spriteName);

	//运行动作
	JumpBy*jump = JumpBy::create(duration,Point(40.f,140.f),-10.f,1);
	RotateBy*rotate = RotateBy::create(duration,60.f);
	RemoveSelf*remove = RemoveSelf::create();

	auto spawn = Spawn::createWithTwoActions(jump,rotate);
	auto seq = Sequence::createWithTwoActions(spawn,remove);

	sprite->runAction(seq);

	return sprite;
}