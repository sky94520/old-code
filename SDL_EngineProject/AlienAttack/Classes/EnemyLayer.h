#ifndef __EnemyLayer_H__
#define __EnemyLayer_H__
#include<list>
#include<vector>
#include<string>
#include<algorithm>
#include "SDL_Engine/SDL_Engine.h"
#include "Enemy.h"

using namespace std;
using namespace SDL;
class GameScene;
/*保存着csv对应的行数*/
enum EnemyProp
{
	kEnemyProp_Name,
	kEnemyProp_Type,
	kEnemyProp_Health,
	kEnemyProp_Speed,
	kEnemyProp_Worth,
	kEnemyProp_FireInterval,
	kEnemyProp_NormalFormat,
	kEnemyProp_NormalCount,
	kEnemyProp_DeadFormat,
	kEnemyProp_DeadCount
};
class Enemy;
class EnemyLayerDelegate
{
public:
	virtual ~EnemyLayerDelegate(){}
	virtual float getMapScrollSpeed()=0;//获取地图滚动速度
	virtual bool addEnemyBullet(const Point&startPos,BulletType type,const Point&heading)=0;
};
/*保存了所有对象，只有在对象将要出现在可视区域内时，才会进行更新*/
class EnemyLayer:public Layer
{
private:
	vector<Enemy*>m_enemys;//保存着所有可用的敌机
	list<Enemy*> m_enemyPool;//敌机池
	//顺序保存着将要出场的敌机
	vector<TMXObject*> m_objects;
	//将要出场的敌机索引
	unsigned int m_objectIndex;
	//地图滚动距离
	float m_scrollDistance;

	EnemyLayerDelegate*m_pDelegate;
public:
	EnemyLayer();
	~EnemyLayer();
	static EnemyLayer*create(vector<TMXObject*> objects);
	bool init(vector<TMXObject*> objects);
	virtual void update(float dt);

	vector<Enemy*>& getEnemys();
	void reset();
	void clear();//恢复最初状态，内部调用了reset
	bool isLevelCompleted();//关卡是否完成
	void setDelegate(EnemyLayerDelegate*pDelegate);
private:
	Enemy*createEnemy(TMXObject*object);
	EnemyType getTypeByString(const string&typeName);

	bool isObsolete(Enemy*enemy);
	void pushEnemyToPool(Enemy*enemy);
	Enemy*popEnemyFromPool();
};
#endif