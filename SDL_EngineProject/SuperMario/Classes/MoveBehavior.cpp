#include "MoveBehavior.h"
#include "BehaviorEntity.h"
#include "BehaviorManager.h"
MoveBehavior::MoveBehavior()
	:m_pDelegate(nullptr)
{
}
void MoveBehavior::setDelegate(BehaviorDelegate*pDelegate)
{
	m_pDelegate = pDelegate;
}
void MoveBehavior::move(BehaviorEntity*entity,float dt,const Point& gravity)
{
	//当道具死亡时，则不进行移动
	if(entity->isDying())
		return;
	//获取当前item的速度
	auto velocity = entity->getVelocity() + gravity;
	//保证速度不大于给定的重力速度
	if(velocity.y > m_pDelegate->getGravity().y)
		velocity.y = m_pDelegate->getGravity().y;

	auto nextVelocity = entity->getVelocity();
	//item的位置
	auto curPos = entity->getPosition();
	//获取精确碰撞面积
	Rect r = entity->getCollisionBoundingBox();
	//判断y轴
	r.origin.y += velocity.y;
	//y轴发生碰撞
	if(velocity.y != 0.f)
	{
		char dir = 0x4;
		if(velocity.y < 0.f)
			dir = 0x8;
		if(m_pDelegate->isCollodedTile(r,dir))
		{
			bool bRet =entity->tileCollidedY(dir&0x4);
			//如果碰撞了就回到一开始的状态
			r.origin.y -= velocity.y;
			velocity.y = 0.f;
			//为true设置为0
			if(bRet)
				nextVelocity.y = 0;
			else
				nextVelocity.y = -nextVelocity.y;
		}
	}
	//判断x轴
	if(velocity.x != 0)
	{
		r.origin.x += velocity.x;
		//设置方向
		char dir = 0x01;
		if(velocity.x < 0.f)
			dir = 0x02;
		//x轴发生碰撞，则x方向相反 如果到达边界，向反方向运动
		//if(m_pDelegate->isCollodedTile(r,dir) || r.origin.x <= 0)
		if(m_pDelegate->isCollidedTileWithCollidedLayer(r,entity,dir) > 0 || r.origin.x <= 0)
		{
			bool bRet = entity->tileCollidedX(dir&0x1);
			nextVelocity.x = -nextVelocity.x;
			velocity.x = nextVelocity.x;
			
		}
	}
	//设置速度和位置
	Point nextPos = curPos + velocity;
	entity->setPosition(nextPos);
	entity->setVelocity(nextVelocity);
}
//------------------------MoveNoWayBehavior-----------------------------------
void MoveNoWayBehavior::performMove(BehaviorEntity*entity,float dt)
{
	//不作任何操作
}
//------------------------MoveWithTileCollidedAndCanDrop----------------------
void MoveWithTileCollidedAndCanDrop::performMove(BehaviorEntity*entity,float dt)
{
	auto gravity = m_pDelegate->getGravity();

	MoveBehavior::move(entity,dt,gravity);
}
//------------------------MoveWithoutGravity--------------------------------
void MoveWithoutGravity::performMove(BehaviorEntity*entity,float dt)
{
	MoveBehavior::move(entity,dt,Point::ZERO);
}
//------------------------MoveOnlyWithVelocity-------------------------------
void MoveOnlyWithVelocity::performMove(BehaviorEntity*entity,float dt)
{
	Point curPos = entity->getPosition();
	Point velocity = entity->getVelocity();

	Point nextPos = curPos + velocity;
	entity->setPosition(nextPos);
}