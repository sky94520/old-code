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
	char sprite;//��ͼ֡
	Weapon*m_pWeapon;

	SDL_SYNTHESIZE(int,m_nCurHP,CurHP);//��ǰѪ��
	SDL_SYNTHESIZE(int,m_nHP,HP);//����Ѫ������
	SDL_SYNTHESIZE(int,m_nAgility,Agility);//��������
	SDL_SYNTHESIZE(int,m_nAtk,Atk);//����������
public:
	Player();
	~Player();

	void bindSprite(char sprite);

	void setPosition(int x,int y);//����λ��
	void setPosition(const Point&pos);

	Point getPosition()const;
	void render();//��Ⱦ
	//����
	void attack(Monster*pMonster);
	//����ʱ����
	void hurt(int damage);
	//����ʱ����
	void dead();
	bool isDead()const;

	void setWeapon(Weapon*pWeapon);
	Weapon*getWeapon()const;
};
#endif