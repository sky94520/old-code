#ifndef __BehaviorManager_H__
#define __BehaviorManager_H__
#include<string>
#include<unordered_map>
#include<vector>
#include<algorithm>
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;
using namespace std;

class MoveBehavior;
class EffectBehavior;
class GameScene;
class Entity;

enum MoveBehaviorType
{
	kMoveNoWayBehaviorType,//不运动
	kMoveWithTileCollidedAndCanDropType,
	kMoveWithoutGravityType,//不受重力 受图块碰撞运动
	kMoveOnlyWithVelocity,//仅跟随速度移动
};
enum EffectBehaviorType
{
	kPlayerLevelUpEffectType,//mario升级效果
	kPlayerCanHurtEnemyEffectType,//吃到星星后的效果
	kPlayerAddCoinEffectType,//增加金币效果
	kPlayerLifeUpEffectType,//增加人的效果
};
class BehaviorDelegate
{
public:
	virtual ~BehaviorDelegate(){}
	virtual bool isCollodedTile(const Rect&r,char dir)=0;
	virtual int isCollidedTileWithCollidedLayer(const Rect&r,Entity*entity,char dir)=0;
	virtual Point getGravity()const=0;
	virtual void addCoin(int coin,Node*node)=0;
	virtual void addScore(int score,Node*node)=0;
	virtual void alterLife(int life)=0;
};
class BehaviorManager:public BehaviorDelegate
{
private:
	static BehaviorManager*m_pInstance;
	unordered_map<MoveBehaviorType,MoveBehavior*> m_moveBehaviors;
	//vector<MoveBehavior*> m_moveBehaviors;
	unordered_map<EffectBehaviorType,EffectBehavior*> m_effectBehaviors;
	GameScene*m_pGameScene;
private:
	BehaviorManager();
	~BehaviorManager();
public:
	static BehaviorManager*getInstance();
	void purge();
	void setGameScene(GameScene*scene);
	//根据类型获取对应的行为
	MoveBehavior*getMoveBehaviorByType(MoveBehaviorType type);
	MoveBehavior*getMoveBehaviorByType(const string&typeName);

	EffectBehavior*getEffectBehaviorByType(EffectBehaviorType type);
private:
	MoveBehavior*createMoveBehavior(MoveBehaviorType type);
	EffectBehavior*createEffectBehavior(EffectBehaviorType type);
	virtual bool isCollodedTile(const Rect&r,char dir);
	virtual int isCollidedTileWithCollidedLayer(const Rect&r,Entity*entity,char dir);

	virtual Point getGravity()const;
	virtual void addCoin(int coin,Node*node);
	virtual void addScore(int score,Node*node);
	virtual void alterLife(int life);
};
#endif