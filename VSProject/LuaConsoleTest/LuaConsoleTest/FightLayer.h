#ifndef __FightLayer_H__
#define __FightLayer_H__
#include<vector>
#include<iostream>
#include<algorithm>
#include "PlatformMarcos.h"
using namespace std;
class Monster;
class Player;
class FightLayer
{
public:
	FightLayer();
	~FightLayer();

	void fight(Player*pPlayer,std::vector<Monster*>*pMonsters);
};
#endif