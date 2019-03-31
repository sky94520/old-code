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
/*子弹在csv的属性列*/
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
/*子弹层，负责子弹的生成和销毁*/
class BulletLayer:public Layer
{
private:
	map<string,vector<Bullet*> > m_bullets;
	list<Bullet*> m_bulletPool;//子弹池，不直接删除而是放入这个，同理，获得也是从这里获得
public:
	BulletLayer();
	~BulletLayer();
	CREATE_FUNC(BulletLayer);
	bool init();

	virtual void update(float dt);
	//生成主角的子弹 起始位置 子弹类型 朝向(仅仅是方向)
	bool addPlayerBullet(const Point&startPos,BulletType type,const Point&heading);
	//敌机子弹 起始位置 子弹类型 朝向(仅仅是方向)
	bool addEnemyBullet(const Point&startPos,BulletType type,const Point&heading);

	std::vector<Bullet*>& getEnemyBullets();
	std::vector<Bullet*>& getPlayerBullets();
	void reset();
private:
	Bullet*createBullet(BulletType type);
	bool isObsolete(Bullet*bullet)const;//子弹是否是废弃的
	std::string getStringByType(BulletType type);

	Bullet*popBulletFromPool();//从子弹池中获取子弹
	void pushBulletToPool(Bullet*bullet);//把子弹放入子弹池中
};
#endif