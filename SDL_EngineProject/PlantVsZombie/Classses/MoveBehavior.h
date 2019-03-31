#ifndef __MoveBehavior_H__
#define __MoveBehavior_H__
class ZombieBase;

class MoveBehavior
{
public:
	virtual void performMove(ZombieBase*zombie) = 0;
};
//----------------LineMoveBehavior---------------------------
class LineMoveBehavior : public MoveBehavior
{
public:
	virtual void performMove(ZombieBase*zombie);
};
#endif