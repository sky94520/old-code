#ifndef __FlyBehavior_H__
#define __FlyBehavior_H__

/*飞行行为，命名规则：用什么飞行，2怎样飞行*/
class Entity;
class FlyBehavior
{
public:
	virtual ~FlyBehavior(){}
	virtual void fly(Entity*entity)=0;
};
//------------------------------SteadyFly匀速飞行--------------------------------------
class SteadyFly:public FlyBehavior
{
public:
	virtual void fly(Entity*entity);
};
#endif