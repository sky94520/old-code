#include "Entity.h"
Entity::Entity():m_bIsCanMove(true)
{
	m_type = ActionType::ACTION_TYPE_NONE;
	m_name = "";
	m_nCurLifeValue = 100;
	m_pIdleAction = NULL;
	m_pWalkAction = NULL;
	m_pAttackNormalActionA = NULL;
	m_pHurtAction = NULL;
	m_pDeadAction = NULL;
}
Entity::~Entity()
{
}
bool Entity::changeState(ActionType type)
{
	if(m_type == ActionType::ACTION_TYPE_DEAD || m_type == type)
		return false;
	this->stopAllActions();
	m_type = type;
	return true;
}
void Entity::runIdleAction()
{
	if(changeState(ActionType::ACTION_TYPE_IDLE))
		this->runAction(m_pIdleAction);
}
void Entity::runWalkAction()
{
	if(changeState(ActionType::ACTION_TYPE_WALK))
		this->runAction(m_pWalkAction);
}
void Entity::runAttackNormalActionA()
{
	if(changeState(ActionType::ACTION_TYPE_NORMAL_ATTACK_A))
		this->runAction(m_pAttackNormalActionA);
}
void Entity::runHurtAction()
{
	if(changeState(ActionType::ACTION_TYPE_HURT))
		this->runAction(m_pHurtAction);
}
void Entity::runDeadAction()
{
	if(changeState(ActionType::ACTION_TYPE_DEAD))
		this->runAction(m_pDeadAction);
}
Animation*Entity::createNormalAction(const char*format,int frameCount,int fps)
{
	return createAttackAction(format,0,frameCount,fps);
}
Animation*Entity::createAttackAction(const char*format,int frameCountBegin,int frameCountEnd,int fps)
{
	Vector<SpriteFrame*> spriteFrames;
	for(int i=frameCountBegin;i<frameCountEnd;i++)
	{
		SpriteFrame*frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format(format,i));
		spriteFrames.pushBack(frame);
	}
	return Animation::createWithSpriteFrames(spriteFrames,1.f/fps);
}
BoundingBox Entity::createBoundingBox(const Vec2 &origin,const Size &size)
{
	BoundingBox boundingBox;
	boundingBox.original.origin = origin;
	boundingBox.original.size = size;

	boundingBox.actual.origin = this->getPosition() + origin;
	boundingBox.actual.size = size;

	return boundingBox;
}
void Entity::updateBoxes()
{
	//通过方向刷新盒子位置
	bool isFlippedX = this->isFlippedX();
	float x = 0.0f;
    if(isFlippedX) 
    {
        x = this->getPosition().x - m_hitBox.original.origin.x;
    }else 
    {
        x = this->getPosition().x + m_hitBox.original.origin.x;
    }
    m_hitBox.actual.origin = Vec2(x, this->getPosition().y + m_hitBox.original.origin.y);
    m_bodyBox.actual.origin = this->getPosition() + m_bodyBox.original.origin;
}
void Entity::setPosition(Vec2 &pos)
{
	//每次重新设定坐标的时候刷新盒子
    Sprite::setPosition(pos);
    this->updateBoxes();
}