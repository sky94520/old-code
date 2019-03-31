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
	vector<Bullet*> m_playerBullets;//�����ӵ�
	vector<Bullet*> m_enemyBullets;//�����ӵ�
	unordered_map<BulletType,list<Bullet*> > m_bulletPool;//�ӵ������

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
	//�ӵ�����ز���
	//�������ӵ�������Ӧ�������úõ�
	//Bullet*popAvaiableItemFromPool();
	template<typename T>
	T popAvaiableItemFromPool(BulletType type);

	void pushItemToPool(Bullet*bullet);
	template<typename T>
	T createBullet(BulletType type);
};
#endif