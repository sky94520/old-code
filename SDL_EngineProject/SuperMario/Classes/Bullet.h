#ifndef __Bullet_H__
#define __Bullet_H__
#include<string>
#include "BehaviorEntity.h"
enum class BulletType
{
	None,
	Mario,//mario���ӵ�
};
using namespace std;
//ֻ��ռ���࣬�����Ժ���չ
class Bullet:public BehaviorEntity
{
	SDL_SYNTHESIZE(BulletType,m_type,BulletType);
protected:
	static const int BULLET_ANIMATION_TAG;
public:
	Bullet();
	~Bullet();

	virtual bool tileCollidedX(bool bRight)=0;
	virtual bool tileCollidedY(bool bDown)=0;

	virtual void runNormalAnimation()=0;//������������
	virtual void reset();
};
//--------------------MarioBullet------------------------------
class MarioBullet:public Bullet
{
	SDL_SYNTHESIZE(float,m_maxHeight,MaxHeight);//mario���ӵ�������Ծ����߶�
private:
	float m_curHeight;
	string m_customName;
public:
	MarioBullet();
	~MarioBullet();
	CREATE_FUNC(MarioBullet);
	bool init();
/*	static MarioBullet*create(const string&customName);
	bool init(const string&customName);*/
	void setCustomName(const string&customName);

	virtual void performMove(float dt);
	virtual bool onHurt(int damage);
	virtual void onDead();

	virtual bool tileCollidedX(bool bRight);
	virtual bool tileCollidedY(bool bDown);

	virtual void runNormalAnimation();
	virtual void reset();
};
#endif