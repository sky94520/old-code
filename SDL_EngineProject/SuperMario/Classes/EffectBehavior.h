#ifndef __EffectBehavior_H__
#define __EffectBehavior_H__
class BehaviorDelegate;
class Player;
class Item;

class EffectBehavior
{
protected:
	BehaviorDelegate*m_pDelegate;
public:
	EffectBehavior();
	virtual ~EffectBehavior(){}
	virtual void performEffect(Item*item,Player*player)=0;
	void setDelegate(BehaviorDelegate*pDelegate);
};
//---------------------------------PlayerLevelUpEffect----------------------------
class PlayerLevelUpEffect:public EffectBehavior
{
public:
	virtual void performEffect(Item*item,Player*player);
};
//---------------------------------PlayerCanHurtEnemyEffect--------------------------
class PlayerCanHurtEnemyEffect:public EffectBehavior
{
public:
	virtual void performEffect(Item*item,Player*player);
};
//---------------------------------PlayerAddCoinEffect--------------------------------
class PlayerAddCoinEffect:public EffectBehavior
{
public:
	virtual void performEffect(Item*item,Player*player);
};
//---------------------------------PlayerLifeUpEffect--------------------------------
class PlayerLifeUpEffect:public EffectBehavior
{
public:
	virtual void performEffect(Item*,Player*player);
};
#endif