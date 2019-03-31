#ifndef __ZombieLayer_H__
#define __ZombieLayer_H__
#include <map>
#include<vector>
#include<string>
#include<algorithm>
#include "SDL_Engine/SDL_Engine.h"

using namespace std;
using namespace SDL;
class ZombieBase;
class ZombieFactory;
struct ZombiePath;
class Terrain;
class Plant;
class Character;
enum class Direction;

class ZombieLayerDelegate
{
public:
	virtual Terrain*findTerrainOfZombieCollision(ZombieBase*zombie)=0;
	virtual Plant*getTopPlantOfAttack(Terrain*terrain) = 0;
	virtual Character*findFirsCollidedMovableCharacterOfRow(int row,Direction attackDir,const Rect& rect) = 0;
};

class ZombieLayer : public Layer
{
private:
	map<int,vector<ZombieBase*> > m_zombies;
	//TODO��չʹ��
	vector<ZombiePath*> m_zombiePaths;
	ZombieFactory*m_pZombieFactory;
	ZombieLayerDelegate*m_pDelegate;
public:
	ZombieLayer();
	~ZombieLayer();
	CREATE_FUNC(ZombieLayer);
	bool init();

	virtual void update(float dt);
	//���ɽ�ʬ
	ZombieBase*makeZombie(const string&zombieName,int row);
	void setZombiePaths(const vector<ZombiePath*>& paths);
	//����ί��
	void setDelegate(ZombieLayerDelegate*pDelegate);
	vector<ZombieBase*> getZombiesOfRow(int row);
	//��ȡȫ���Ľ�ʬ
	map<int,vector<ZombieBase*> >& getZombies();
	//�Ƴ�ָ���Ľ�ʬ
	bool removeZombie(ZombieBase*zombie,bool cleanup = false);
private:
	void zombieUpdate(ZombieBase*zombie,float dt);
	static bool zombieComparisonLess(ZombieBase* n1, ZombieBase* n2);
};
#endif