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
	list<Item*> m_itemPool;//���߶���أ�������߶���ĸ���
	vector<Item*> m_items;

	ItemLayerDelegate*m_pDelegate;
public:
	ItemLayer();
	~ItemLayer();
	CREATE_FUNC(ItemLayer);
	bool init();
	virtual void update(float dt);
	//���𴴽����ֵ���
	bool produceItemByType(TMXObject*object);
	void setDelegate(ItemLayerDelegate*pDelegate);
	vector<Item*> &getItems();
private:
	//��������������Ļ��Ϊ����״̬
	bool isObsolete(Item*item);
	//���߳�
	Item*popAvaiableItemFromPool();
	template<typename T>
	T popAvaiableItemFromPool(ItemType type);

	void pushItemToPool(Item*item);
	//�����ɳ�����
	/*Item*createMushroom();
	//��������
	Item*createStar();
	TileCoin*createCoin(TMXObject*object);*/
	bool createCommonItem(TMXObject*object);
	bool createTileCoinItem(TMXObject*object);
};
#endif