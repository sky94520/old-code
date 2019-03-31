#ifndef __Weapon_H__
#define __Weapon_H__
#include<string>
#include<vector>
#include "PlatformMarcos.h"
#include "Item.h"
class Player;
class Monster;
class Weapon : public Item
{
	SDL_SYNTHESIZE(int,m_nAtk,Atk);//�����˺�
	SDL_SYNTHESIZE(int,m_nCurDurability,CurDurability);//��ǰ�;ö�
	SDL_SYNTHESIZE(int,m_nDurability,Durability);//�;ö�
private:
	Player*m_pOwner;
public:
	Weapon();
	~Weapon();

	virtual bool init(const std::string&stringID);
	virtual void use();
	virtual std::string toString()const;

	void setOwner(Player*pPlayer);
	Player*getOwner()const;

	bool isEquipped()const;
private:
	void attack();
};
#endif