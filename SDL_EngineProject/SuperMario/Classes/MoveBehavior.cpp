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
	//����������ʱ���򲻽����ƶ�
	if(entity->isDying())
		return;
	//��ȡ��ǰitem���ٶ�
	auto velocity = entity->getVelocity() + gravity;
	//��֤�ٶȲ����ڸ����������ٶ�
	if(velocity.y > m_pDelegate->getGravity().y)
		velocity.y = m_pDelegate->getGravity().y;

	auto nextVelocity = entity->getVelocity();
	//item��λ��
	auto curPos = entity->getPosition();
	//��ȡ��ȷ��ײ���
	Rect r = entity->getCollisionBoundingBox();
	//�ж�y��
	r.origin.y += velocity.y;
	//y�ᷢ����ײ
	if(velocity.y != 0.f)
	{
		char dir = 0x4;
		if(velocity.y < 0.f)
			dir = 0x8;
		if(m_pDelegate->isCollodedTile(r,dir))
		{
			bool bRet =entity->tileCollidedY(dir&0x4);
			//�����ײ�˾ͻص�һ��ʼ��״̬
			r.origin.y -= velocity.y;
			velocity.y = 0.f;
			//Ϊtrue����Ϊ0
			if(bRet)
				nextVelocity.y = 0;
			else
				nextVelocity.y = -nextVelocity.y;
		}
	}
	//�ж�x��
	if(velocity.x != 0)
	{
		r.origin.x += velocity.x;
		//���÷���
		char dir = 0x01;
		if(velocity.x < 0.f)
			dir = 0x02;
		//x�ᷢ����ײ����x�����෴ �������߽磬�򷴷����˶�
		//if(m_pDelegate->isCollodedTile(r,dir) || r.origin.x <= 0)
		if(m_pDelegate->isCollidedTileWithCollidedLayer(r,entity,dir) > 0 || r.origin.x <= 0)
		{
			bool bRet = entity->tileCollidedX(dir&0x1);
			nextVelocity.x = -nextVelocity.x;
			velocity.x = nextVelocity.x;
			
		}
	}
	//�����ٶȺ�λ��
	Point nextPos = curPos + velocity;
	entity->setPosition(nextPos);
	entity->setVelocity(nextVelocity);
}
//------------------------MoveNoWayBehavior-----------------------------------
void MoveNoWayBehavior::performMove(BehaviorEntity*entity,float dt)
{
	//�����κβ���
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