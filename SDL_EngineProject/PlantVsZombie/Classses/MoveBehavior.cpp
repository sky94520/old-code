#include "MoveBehavior.h"
#include "ZombieBase.h"

void LineMoveBehavior::performMove(ZombieBase*zombie)
{
	auto dir = zombie->getDir();
	auto curPos = zombie->getPosition();
	float speed = zombie->getCurSpeed();
	Point nextPos;

	if (dir == Direction::Left)
	{
		nextPos = curPos - Point(speed,0.f);

		zombie->setSpriteFlipX(false);
	}
	else if (dir == Direction::Right)
	{
		nextPos = curPos + Point(speed,0.f);
		
		zombie->setSpriteFlipX(true);
	}
	zombie->setPosition(nextPos);
}