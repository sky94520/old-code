#ifndef __BulletLayer_H__
#define __BulletLayer_H__
#include<map>
#include<list>
#include<string>
#include<vector>
#include "SDL_Engine/SDL_Engine.h"
#include "Bullet.h"

using namespace SDL;
using namespace std;
/*�ӵ���csv��������*/
enum CsvBulletProp
{
	kBulletProp_Name,
	kBulletProp_Type,
	kBulletProp_Speed,
	kBulletProp_Damage,
	kBulletProp_NormalFormat,
	kBulletProp_NormalCount,
	kBulletProp_DeadFormat,
	kBulletProp_DeadCount,
};
/*�ӵ��㣬�����ӵ������ɺ�����*/
class BulletLayer:public Layer
{
private:
	map<string,vector<Bullet*> > m_bullets;
	list<Bullet*> m_bulletPool;//�ӵ��أ���ֱ��ɾ�����Ƿ��������ͬ�����Ҳ�Ǵ�������
public:
	BulletLayer();
	~BulletLayer();
	CREATE_FUNC(BulletLayer);
	bool init();

	virtual void update(float dt);
	//�������ǵ��ӵ� ��ʼλ�� �ӵ����� ����(�����Ƿ���)
	bool addPlayerBullet(const Point&startPos,BulletType type,const Point&heading);
	//�л��ӵ� ��ʼλ�� �ӵ����� ����(�����Ƿ���)
	bool addEnemyBullet(const Point&startPos,BulletType type,const Point&heading);

	std::vector<Bullet*>& getEnemyBullets();
	std::vector<Bullet*>& getPlayerBullets();
	void reset();
private:
	Bullet*createBullet(BulletType type);
	bool isObsolete(Bullet*bullet)const;//�ӵ��Ƿ��Ƿ�����
	std::string getStringByType(BulletType type);

	Bullet*popBulletFromPool();//���ӵ����л�ȡ�ӵ�
	void pushBulletToPool(Bullet*bullet);//���ӵ������ӵ�����
};
#endif