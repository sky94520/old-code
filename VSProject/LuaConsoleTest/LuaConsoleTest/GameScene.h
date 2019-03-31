#ifndef __GameScene_H__
#define __GameScene_H__
#include<vector>
#include<cstdlib>
#include<ctime>
#include "PackageLayer.h"
#include "PlatformMarcos.h"
#include "FieldMap.h"

using namespace std;
class Player;
class Weapon;
class Monster;
class FightLayer;
class Colliabled;
class Item;
class GameScene:public PackageLayerDelegate,public FieldMapDelegate
{
private:
	Player*m_pPlayer;
	PackageLayer*m_pPackageLayer;//背包界面
	FieldMap*m_pMap;//地图相关界面
	FightLayer*m_pFightLayer;//战斗场面
	Colliabled*m_pColliabledEntity;//当前碰撞实体
public:
	GameScene();
	~GameScene();
	bool init();

	void render();

	Player*getPlayer()const;
	std::vector<Monster*>* getMonsters();

	void showPackage();

	void setColliabledEntity(Colliabled*pColliabled);
	Colliabled*getColliabledEntity()const;
private://Delegate
	bool use(Item*pItem);
	int sell(Item*pItem);//出售装备

	virtual void fight();//开始战斗

	virtual void toggleLayer(const std::string&filename,const Point&playerPos);
};
#endif