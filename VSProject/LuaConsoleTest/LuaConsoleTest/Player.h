#ifndef __Player_H__
#define __Player_H__
#include<cstdio>
#include<vector>
#include<algorithm>
#include "Point.h"
#include "PlatformMarcos.h"
class Weapon;
class Monster;
class Player
{
private:
	Point position;
	char sprite;//绘图帧
	Weapon*m_pWeapon;

	SDL_SYNTHESIZE(int,m_nCurHP,CurHP);//当前血量
	SDL_SYNTHESIZE(int,m_nHP,HP);//基础血量上限
	SDL_SYNTHESIZE(int,m_nAgility,Agility);//基础敏捷
	SDL_SYNTHESIZE(int,m_nAtk,Atk);//基础攻击力
public:
	Player();
	~Player();

	void bindSprite(char sprite);

	void setPosition(int x,int y);//设置位置
	void setPosition(const Point&pos);

	Point getPosition()const;
	void render();//渲染
	//攻击
	void attack(Monster*pMonster);
	//受伤时调用
	void hurt(int damage);
	//死亡时调用
	void dead();
	bool isDead()const;

	void setWeapon(Weapon*pWeapon);
	Weapon*getWeapon()const;
};
#endif