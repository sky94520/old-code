#ifndef __Item_H__
#define __Item_H__
#include "SDL_Engine/SDL_Engine.h"
#include "BehaviorEntity.h"

using namespace SDL;
class EffectBehavior;
class MoveBehavior;
class Player;

enum ItemType
{
	kItemType_Mushroom,//蘑菇，吃了mario会长大
	kItemType_Flower,//花，吃了mario会发射子弹
	kItemType_Star,//星星，吃了会使mario无敌
	kItemType_TileCoin,//砖块金币，这里指在砖块里的金币
};
/*道具，目前包括 蘑菇 花*/
class Item:public BehaviorEntity
{
	SDL_BOOL_SYNTHESIZE(m_bUpdate,Update);//是否应该开始更新
	SDL_SYNTHESIZE(ItemType,m_type,ItemType);//道具类型
private:
	EffectBehavior*m_pEffectBehavior;
public:
	Item();
	~Item();
	CREATE_FUNC(Item);
	bool init();

	//行为更新
	void performEffect(Player*player);
	virtual void performMove(float dt);
	//设置行为
	void setEffectBehavior(EffectBehavior*effectBehavior);
	//运行正常动画
	virtual void runNormalAnimation();
	//重置
	virtual void onDead();
	virtual void reset();
	virtual bool tileCollidedX(bool bRight);
	virtual bool tileCollidedY(bool bDown);
	virtual	Rect getCollisionBoundingBox()const;
};
//----------------------------------星星----------------------------
class Star:public Item
{
private:
	float const MAX_JUMP_HEIGHT;//星星跳跃的最高距离
	float m_curJumpHeight;
public:
	Star();
	~Star();
	CREATE_FUNC(Star);
	bool init();

	virtual void reset();
	virtual void performMove(float dt);
	virtual bool tileCollidedX(bool bRight);
	virtual bool tileCollidedY(bool bDown);
};
//-----------------------------TileCoin------------------------------
class TileCoin:public Item
{
	SDL_SYNTHESIZE(int,m_nCoinCount,CoinCount);//当前的金币数量
private:
	float m_elpased;//当前流逝值
	TMXObject*m_pObject;//保存tmx对象
public:
	TileCoin();
	~TileCoin();
	CREATE_FUNC(TileCoin);
	bool init();
	//和tmx对象联结
	void associateWithTMXObject(TMXObject*object);
	TMXObject*getTMXObject()const{return m_pObject;}
	void setTMXObject(TMXObject*object){m_pObject = object;}

	//virtual void performEffect(Player*player);
	virtual bool onHurt(int damage);
	virtual void reset();
	virtual void performMove(float dt);
};
#endif