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
	//����㶹�ӵ� TODO
	Bullet*addPeaBullet();
	//��ӱ�ը
	Boom*addBoom();
	//��Ӿ��Ĳ�
	CabbageBullet*addCabbageBullet();
	//�������
	CornpultBullet*addCornpultBullet(bool isButter);
	//��Ӻ����㶹
	SnowPeaBullet*addSnowPeaBullet();
	//��ӻ��㶹
	FirePeaBullet*addFirePeaBullet();
	//��������㶹��
	ShooterPeaBullet*addShooterPeaBullet(ShooterPeaBullet::Type type);
	//��Ӵ��繽�ӵ�
	FumeShroomBullet*addFumeShroomBullet();
	//����繽�ӵ�
	ShroomBullet* addShroomBullet();
	//��ȡ�ӵ�����
	vector<Bullet*>& getBulletList();

	void setDelegate(BulletLayerDelegate*pDelegate);

	static FiniteTimeAction*lineRoute(Bullet *bullet,const Point& deltaPos,float speed,bool bRight);
	static FiniteTimeAction*jumpRoute(Bullet *bullet,const Point& startPos,const Point& endPos,float speed);

private:
	void checkCollisionBetweenZombieAndBullet(Bullet*bullet);
	void handleCollision(Bullet*bullet,ZombieBase*zombie);
};
#endif