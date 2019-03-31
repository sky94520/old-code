#ifndef __BulletLayer_H__
#define __BulletLayer_H__
#include<vector>
#include "SDL_Engine/SDL_Engine.h"
#include "ShooterPeaBullet.h"

using namespace std;
using namespace SDL;

class Bullet;
class ZombieBase;
class Boom;
class CabbageBullet;
class SnowPeaBullet;
class FirePeaBullet;
class FumeShroomBullet;
class ShroomBullet;
class CornpultBullet;

class BulletLayerDelegate
{
public:
	virtual ~BulletLayerDelegate(){}
	virtual vector<ZombieBase*> getZombiesOfRow(int row)=0;
};

class BulletLayer : public Layer
{
private:
	vector<Bullet*> m_bullets;
	BulletLayerDelegate*m_pDelegate;
public:
	BulletLayer();
	~BulletLayer();
	CREATE_FUNC(BulletLayer);
	bool init();
	void update(float dt);
	//添加豌豆子弹 TODO
	Bullet*addPeaBullet();
	//添加爆炸
	Boom*addBoom();
	//添加卷心菜
	CabbageBullet*addCabbageBullet();
	//添加玉米
	CornpultBullet*addCornpultBullet(bool isButter);
	//添加寒冰豌豆
	SnowPeaBullet*addSnowPeaBullet();
	//添加火豌豆
	FirePeaBullet*addFirePeaBullet();
	//添加射手豌豆弹
	ShooterPeaBullet*addShooterPeaBullet(ShooterPeaBullet::Type type);
	//添加大喷菇子弹
	FumeShroomBullet*addFumeShroomBullet();
	//添加喷菇子弹
	ShroomBullet* addShroomBullet();
	//获取子弹数组
	vector<Bullet*>& getBulletList();

	void setDelegate(BulletLayerDelegate*pDelegate);

	static FiniteTimeAction*lineRoute(Bullet *bullet,const Point& deltaPos,float speed,bool bRight);
	static FiniteTimeAction*jumpRoute(Bullet *bullet,const Point& startPos,const Point& endPos,float speed);

private:
	void checkCollisionBetweenZombieAndBullet(Bullet*bullet);
	void handleCollision(Bullet*bullet,ZombieBase*zombie);
};
#endif