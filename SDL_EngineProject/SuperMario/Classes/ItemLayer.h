#ifndef __ItemLayer_H__
#define __ItemLayer_H__
#include<list>
#include<vector>
#include<string>
#include "Item.h"
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;
using namespace std;
class Item;
class Player;
class ItemLayerDelegate
{
public:
	virtual ~ItemLayerDelegate(){}
	virtual TMXLayer*getEntityLayer()const=0;
	virtual Player*getPlayer()const=0;
};
class ItemLayer:public Layer
{
private:
	list<Item*> m_itemPool;//道具对象池，负责道具对象的复用
	vector<Item*> m_items;

	ItemLayerDelegate*m_pDelegate;
public:
	ItemLayer();
	~ItemLayer();
	CREATE_FUNC(ItemLayer);
	bool init();
	virtual void update(float dt);
	//负责创建各种道具
	bool produceItemByType(TMXObject*object);
	void setDelegate(ItemLayerDelegate*pDelegate);
	vector<Item*> &getItems();
private:
	//道具死亡或者屏幕就为废弃状态
	bool isObsolete(Item*item);
	//道具池
	Item*popAvaiableItemFromPool();
	template<typename T>
	T popAvaiableItemFromPool(ItemType type);

	void pushItemToPool(Item*item);
	//创建成长道具
	/*Item*createMushroom();
	//创建星星
	Item*createStar();
	TileCoin*createCoin(TMXObject*object);*/
	bool createCommonItem(TMXObject*object);
	bool createTileCoinItem(TMXObject*object);
};
#endif