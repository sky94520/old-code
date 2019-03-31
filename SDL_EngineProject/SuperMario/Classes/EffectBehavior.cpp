#include "EffectBehavior.h"
#include "BehaviorManager.h"
#include "Item.h"
#include "Player.h"
#include "DynamicData.h"

EffectBehavior::EffectBehavior()
	:m_pDelegate(nullptr)
{
}
void EffectBehavior::setDelegate(BehaviorDelegate*pDelegate)
{
	m_pDelegate = pDelegate;
}
//---------------------------------PlayerLevelUpEffect----------------------------
void PlayerLevelUpEffect::performEffect(Item*item,Player*player)
{
	//道具无效
	if(item->isDying())
		return;
	player->levelUp();
}
void PlayerCanHurtEnemyEffect::performEffect(Item*item,Player*player)
{
	//道具无效
	if(item->isDying())
		return;
	player->canHurtEnemyWithInvulnearability();
}
//---------------------------------PlayerAddCoinEffect--------------------------------
void PlayerAddCoinEffect::performEffect(Item*item,Player*player)
{
	if(item->isDying())
		return ;
	//todo
	//player->addCoin();
	//增加金币
	m_pDelegate->addCoin(1,item);
	//增加分数
	m_pDelegate->addScore(100,item);
}
//---------------------------------PlayerLifeUpEffect--------------------------------
void PlayerLifeUpEffect::performEffect(Item*item,Player*player)
{
	if(item->isDying())
		return ;
	//增加生命
	m_pDelegate->alterLife(1);
}