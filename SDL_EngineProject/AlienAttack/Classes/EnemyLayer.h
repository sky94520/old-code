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
/*������csv��Ӧ������*/
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
	virtual float getMapScrollSpeed()=0;//��ȡ��ͼ�����ٶ�
	virtual bool addEnemyBullet(const Point&startPos,BulletType type,const Point&heading)=0;
};
/*���������ж���ֻ���ڶ���Ҫ�����ڿ���������ʱ���Ż���и���*/
class EnemyLayer:public Layer
{
private:
	vector<Enemy*>m_enemys;//���������п��õĵл�
	list<Enemy*> m_enemyPool;//�л���
	//˳�򱣴��Ž�Ҫ�����ĵл�
	vector<TMXObject*> m_objects;
	//��Ҫ�����ĵл�����
	unsigned int m_objectIndex;
	//��ͼ��������
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
	void clear();//�ָ����״̬���ڲ�������reset
	bool isLevelCompleted();//�ؿ��Ƿ����
	void setDelegate(EnemyLayerDelegate*pDelegate);
private:
	Enemy*createEnemy(TMXObject*object);
	EnemyType getTypeByString(const string&typeName);

	bool isObsolete(Enemy*enemy);
	void pushEnemyToPool(Enemy*enemy);
	Enemy*popEnemyFromPool();
};
#endif