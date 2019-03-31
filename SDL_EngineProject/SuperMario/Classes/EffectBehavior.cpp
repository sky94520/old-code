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
	//������Ч
	if(item->isDying())
		return;
	player->levelUp();
}
void PlayerCanHurtEnemyEffect::performEffect(Item*item,Player*player)
{
	//������Ч
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
	//���ӽ��
	m_pDelegate->addCoin(1,item);
	//���ӷ���
	m_pDelegate->addScore(100,item);
}
//---------------------------------PlayerLifeUpEffect--------------------------------
void PlayerLifeUpEffect::performEffect(Item*item,Player*player)
{
	if(item->isDying())
		return ;
	//��������
	m_pDelegate->alterLife(1);
}