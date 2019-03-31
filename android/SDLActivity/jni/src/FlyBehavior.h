#ifndef __FlyBehavior_H__
#define __FlyBehavior_H__

/*������Ϊ������������ʲô���У�2��������*/
class Entity;
class FlyBehavior
{
public:
	virtual ~FlyBehavior(){}
	virtual void fly(Entity*entity)=0;
};
//------------------------------SteadyFly���ٷ���--------------------------------------
class SteadyFly:public FlyBehavior
{
public:
	virtual void fly(Entity*entity);
};
#endif