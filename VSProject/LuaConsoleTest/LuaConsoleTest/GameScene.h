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
	PackageLayer*m_pPackageLayer;//��������
	FieldMap*m_pMap;//��ͼ��ؽ���
	FightLayer*m_pFightLayer;//ս������
	Colliabled*m_pColliabledEntity;//��ǰ��ײʵ��
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
	int sell(Item*pItem);//����װ��

	virtual void fight();//��ʼս��

	virtual void toggleLayer(const std::string&filename,const Point&playerPos);
};
#endif