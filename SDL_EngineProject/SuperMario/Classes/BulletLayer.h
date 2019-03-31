#ifndef __BulletLayer_H__
#define __BulletLayer_H__
#include<list>
#include<vector>
#include<unordered_map>
#include "SDL_Engine/SDL_Engine.h"
#include "Bullet.h"

using namespace SDL;
using namespace std;
class BulletLayerDelegate
{
public:
	virtual ~BulletLayerDelegate(){}
	virtual TMXLayer*getEntityLayer()const=0;
};
class BulletLayer:public Layer
{
private:
	vector<Bullet*> m_playerBullets;//主角子弹
	vector<Bullet*> m_enemyBullets;//怪物子弹
	unordered_map<BulletType,list<Bullet*> > m_bulletPool;//子弹对象池

	BulletLayerDelegate*m_pDelegate;
public:
	BulletLayer();
	~BulletLayer();
	CREATE_FUNC(BulletLayer);
	bool init();
	void update(float dt);

	void addPlayerBullet(BulletType bulletType,const Point&startPos,const Point&heading,const string&id);
	void addEnemyBullet(BulletType bulletType,const Point&heading);

	void setDelegate(BulletLayerDelegate*pDelegate);
	vector<Bullet*>& getPlayerBullets(){return m_playerBullets;}
private:
	bool isObsolete(Bullet*bullet);
	//子弹池相关操作
	//弹出的子弹的属性应该是设置好的
	//Bullet*popAvaiableItemFromPool();
	template<typename T>
	T popAvaiableItemFromPool(BulletType type);

	void pushItemToPool(Bullet*bullet);
	template<typename T>
	T createBullet(BulletType type);
};
#endif