#ifndef __Monster_H__
#define __Monster_H__
#include<string>
#include "PlatformMarcos.h"
class Player;
class Monster
{
private:
	SDL_SYNTHESIZE(std::string,m_ID,ID);
	SDL_SYNTHESIZE(std::string,m_name,Name);
	SDL_SYNTHESIZE(std::string,m_description,Description);
	SDL_SYNTHESIZE(int,m_nHP,HP);
	SDL_SYNTHESIZE(int,m_nCurHP,CurHP);//��ǰHP
	SDL_SYNTHESIZE(int,m_nDamage,Damage);//�˺�
	SDL_SYNTHESIZE(int,m_nAgility,Agility);//����
	SDL_SYNTHESIZE(int,m_nGold,Gold);//Я���Ľ����Ŀ
public:
	Monster();
	~Monster();
	bool init(const std::string&id);
	void attack(Player*pPlayer);
	void hurt(int damage);
	void dead();

	bool isDead()const;
};
#endif