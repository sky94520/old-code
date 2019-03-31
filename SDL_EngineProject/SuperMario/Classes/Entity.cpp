#include "Entity.h"

Entity::Entity()
	:m_pSprite(nullptr),m_nCurHp(0),m_nMaxHp(0)
	,m_bDead(false),m_nDamage(0)
{
}
Entity::~Entity()
{
}
void Entity::bindSprite(Sprite*sprite)
{
	if(m_pSprite)
		m_pSprite->removeFromParent();

	this->m_pSprite = sprite;
	this->addChild(m_pSprite);

	Size size = m_pSprite->getContentSize();

	m_pSprite->setPosition(size.width/2,size.height/2);
	this->setContentSize(size);
	this->setAnchorPoint(Point(0.5f,0.5f));
	this->onBindSprite();
}
Sprite*Entity::getSprite()const
{
	return m_pSprite;
}
Animate*Entity::createAnimate(std::string format,int begin,int end,float delayPerUnit,unsigned int loops)
{
	vector<SpriteFrame*> frames;
	auto spriteFrameCache = Director::getInstance()->getSpriteFrameCache();
	for(int i=begin;i<=end;i++)
	{
		auto frame = spriteFrameCache->getSpriteFrameByName(StringUtils::format(format.c_str(),i));
		frames.push_back(frame);
	}
	Animation*animation = Animation::createWithSpriteFrames(frames,delayPerUnit,loops);
	if(loops == 1)
		animation->setRestoreOriginalFrame(true);
	return Animate::create(animation);
}
void Entity::hurt(int damage)
{
	//只要受伤就调用这个函数
	bool bRet = onHurt(damage);
	//如果此时已经死亡或者伤害小于0，则不再调用
	if(this->isDying() || this->isDead() || damage <= 0 || bRet == false)
		return;
	int curHp = this->getCurHp();
	int afterHp = curHp - damage;
	
	setCurHp(afterHp);
	if(afterHp <= 0)
		onDead();//死亡时调用
}
bool Entity::isDying()const
{
	return m_nCurHp <= 0;
}

void Entity::onBindSprite()
{
}
bool Entity::onHurt(int damage)
{
	return true;
}
void Entity::onDead()
{
}
bool Entity::isCanBrokeTile()const
{
	return false;
}
bool Entity::isInteractiveWithBlock()const
{
	return false;
}
Rect Entity::getCollisionBoundingBox()const
{
	Rect r;
	//获取最小包围盒
	if(this->getSprite())
		r = this->getSprite()->getSpriteFrameRect();

	//获取左上角坐标 再根据偏移坐标获得准确包围盒
	Point pos = this->getPosition();
	pos -= Point(_anchorPoint.x*_contentSize.width*_scaleX,_anchorPoint.y*_contentSize.height*_scaleY);
	pos += r.origin;
	Rect rect = Rect(pos.x,pos.y,r.size.width,r.size.height);
	return rect;
}