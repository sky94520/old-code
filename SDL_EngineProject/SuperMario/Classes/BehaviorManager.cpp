#include "BehaviorManager.h"
#include "MoveBehavior.h"
#include "GameScene.h"
#include "EffectBehavior.h"

BehaviorManager*BehaviorManager::m_pInstance = nullptr;

BehaviorManager::BehaviorManager()
	:m_pGameScene(nullptr)
{
}
BehaviorManager::~BehaviorManager()
{
	//清除变量
	for(auto iter = m_moveBehaviors.begin();iter != m_moveBehaviors.end();)
	{
		auto behavior = iter->second;
		iter = m_moveBehaviors.erase(iter);
		delete behavior;
	}
	for(auto iter = m_effectBehaviors.begin();iter != m_effectBehaviors.end();)
	{
		auto behavior = iter->second;
		delete behavior;
		iter = m_effectBehaviors.erase(iter);
	}
}
BehaviorManager*BehaviorManager::getInstance()
{
	if(m_pInstance == nullptr)
		m_pInstance = new BehaviorManager();
	return m_pInstance;
}
void BehaviorManager::purge()
{
	SDL_SAFE_DELETE(m_pInstance);
}
void BehaviorManager::setGameScene(GameScene*scene)
{
	m_pGameScene = scene;
}
MoveBehavior*BehaviorManager::getMoveBehaviorByType(MoveBehaviorType type)
{
	auto iter = m_moveBehaviors.find(type);
	MoveBehavior*behavior = nullptr;
	//新建移动行为
	if(iter == m_moveBehaviors.end())
	{
		behavior = this->createMoveBehavior(type);
		m_moveBehaviors.insert(make_pair(type,behavior));
	}
	else
		behavior = iter->second;
	return behavior;
}
MoveBehavior*BehaviorManager::getMoveBehaviorByType(const string&typeName)
{
	MoveBehaviorType type = kMoveNoWayBehaviorType;
	if(typeName == "kMoveNoWayBehaviorType")
		type = kMoveNoWayBehaviorType;
	else if(typeName == "kMoveWithTileCollidedAndCanDropType")
		type = kMoveWithTileCollidedAndCanDropType;
	else if(typeName == "kMoveWithoutGravityType")
		type = kMoveWithoutGravityType;
	else if(typeName == "kMoveOnlyWithVelocity")
		type = kMoveOnlyWithVelocity;
	return this->getMoveBehaviorByType(type);
}
EffectBehavior*BehaviorManager::getEffectBehaviorByType(EffectBehaviorType type)
{
	auto iter = m_effectBehaviors.find(type);
	EffectBehavior*behavior = nullptr;
	//新建移动行为
	if(iter == m_effectBehaviors.end())
	{
		behavior = this->createEffectBehavior(type);
		m_effectBehaviors.insert(make_pair(type,behavior));
	}
	else
		behavior = iter->second;
	
	return behavior;
}
MoveBehavior*BehaviorManager::createMoveBehavior(MoveBehaviorType type)
{
	MoveBehavior*behavior = nullptr;
	switch(type)
	{
	case kMoveWithTileCollidedAndCanDropType:
		{
			behavior = new MoveWithTileCollidedAndCanDrop();
		}break;
	case kMoveWithoutGravityType:
		{
			behavior = new MoveWithoutGravity();
		}break;
	case kMoveOnlyWithVelocity:
		{
			behavior = new MoveOnlyWithVelocity();
		}break;
	case kMoveNoWayBehaviorType:
	default:
		behavior = new MoveNoWayBehavior();
	}
	behavior->setDelegate(this);
	return behavior;
}
EffectBehavior*BehaviorManager::createEffectBehavior(EffectBehaviorType type)
{
	EffectBehavior*behavior = nullptr;
	switch(type)
	{
	case kPlayerLevelUpEffectType:behavior = new PlayerLevelUpEffect();break;
	case kPlayerCanHurtEnemyEffectType:behavior = new PlayerCanHurtEnemyEffect();break;
	case kPlayerAddCoinEffectType:behavior = new PlayerAddCoinEffect();break;
	case kPlayerLifeUpEffectType:behavior = new PlayerLifeUpEffect();break;
	}
	behavior->setDelegate(this);
	return behavior;
}
//delegate
bool BehaviorManager::isCollodedTile(const Rect&r,char dir)
{
	return m_pGameScene->isCollidedTileWithCollidedLayer(r,dir) > 0;
}
int BehaviorManager::isCollidedTileWithCollidedLayer(const Rect&r,Entity*entity,char dir)
{
	return m_pGameScene->isCollidedTileWithCollidedLayer(r,entity,dir);
}
Point BehaviorManager::getGravity()const
{
	return m_pGameScene->getGravity();
}
void BehaviorManager::addCoin(int coin,Node*node)
{
	m_pGameScene->addCoin(coin,node);
}
void BehaviorManager::addScore(int score,Node*node)
{
	m_pGameScene->addScore(score,node);
}
void BehaviorManager::alterLife(int life)
{
	m_pGameScene->alterLife(life);
}