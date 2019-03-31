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
	kItemType_Mushroom,//Ģ��������mario�᳤��
	kItemType_Flower,//��������mario�ᷢ���ӵ�
	kItemType_Star,//���ǣ����˻�ʹmario�޵�
	kItemType_TileCoin,//ש���ң�����ָ��ש����Ľ��
};
/*���ߣ�Ŀǰ���� Ģ�� ��*/
class Item:public BehaviorEntity
{
	SDL_BOOL_SYNTHESIZE(m_bUpdate,Update);//�Ƿ�Ӧ�ÿ�ʼ����
	SDL_SYNTHESIZE(ItemType,m_type,ItemType);//��������
private:
	EffectBehavior*m_pEffectBehavior;
public:
	Item();
	~Item();
	CREATE_FUNC(Item);
	bool init();

	//��Ϊ����
	void performEffect(Player*player);
	virtual void performMove(float dt);
	//������Ϊ
	void setEffectBehavior(EffectBehavior*effectBehavior);
	//������������
	virtual void runNormalAnimation();
	//����
	virtual void onDead();
	virtual void reset();
	virtual bool tileCollidedX(bool bRight);
	virtual bool tileCollidedY(bool bDown);
	virtual	Rect getCollisionBoundingBox()const;
};
//----------------------------------����----------------------------
class Star:public Item
{
private:
	float const MAX_JUMP_HEIGHT;//������Ծ����߾���
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
	SDL_SYNTHESIZE(int,m_nCoinCount,CoinCount);//��ǰ�Ľ������
private:
	float m_elpased;//��ǰ����ֵ
	TMXObject*m_pObject;//����tmx����
public:
	TileCoin();
	~TileCoin();
	CREATE_FUNC(TileCoin);
	bool init();
	//��tmx��������
	void associateWithTMXObject(TMXObject*object);
	TMXObject*getTMXObject()const{return m_pObject;}
	void setTMXObject(TMXObject*object){m_pObject = object;}

	//virtual void performEffect(Player*player);
	virtual bool onHurt(int damage);
	virtual void reset();
	virtual void performMove(float dt);
};
#endif