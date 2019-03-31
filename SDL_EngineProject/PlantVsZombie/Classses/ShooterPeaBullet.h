#ifndef __ShooterPeaBullet_H__
#define __ShooterPeaBullet_H__
#include<string>
#include "Bullet.h"
using namespace std;

class ShooterPeaBullet : public Bullet
{
public:
	enum class Type
	{
		PeaBullet,/*普通子弹*/
		SnowPeaBullet,/*雪花子弹*/
		FirePeaBullet,/*火焰弹*/
	};
private:
	Bullet*m_pInnerBullet;
	Type m_type;
public:
	ShooterPeaBullet();
	~ShooterPeaBullet();
	static ShooterPeaBullet*create(Type type);
	bool init(Type type);

	bool transformType(Type type);
	Type getShooterPeaBulletType()const;
	virtual void onHurt();
	//碰撞结束后调用
	virtual void contactEnd();
	virtual Rect getCollisionBoundingBox()const;
private:
	Bullet*makePlant(Type type);
	void setProperties(Bullet*bullet);
	void dead();
};
#endif