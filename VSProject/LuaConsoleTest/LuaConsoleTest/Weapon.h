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
	SDL_SYNTHESIZE(int,m_nAtk,Atk);//ÎäÆ÷ÉËº¦
	SDL_SYNTHESIZE(int,m_nCurDurability,CurDurability);//µ±Ç°ÄÍ¾Ã¶È
	SDL_SYNTHESIZE(int,m_nDurability,Durability);//ÄÍ¾Ã¶È
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