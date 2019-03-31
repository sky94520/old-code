#ifndef __Product_H__
#define __Product_H__

#include "SDL_Engine/SDL_Engine.h"
#include "Entity.h"

using namespace SDL;

enum class ProductType
{
	None,
	Sun,//太阳
	Gold,//金币
};

class Product:public Entity
{
	SDL_SYNTHESIZE(ProductType,m_productType,ProductType);
	SDL_SYNTHESIZE(int,m_nNumber,Number);
	SDL_BOOL_SYNTHESIZE(m_bClicked,Clicked);//是否已经点击
	SDL_BOOL_SYNTHESIZE(m_bUpdate,Update);//是否开始更新
	SDL_BOOL_SYNTHESIZE(m_bDead,Dead);//是否死亡
	SDL_SYNTHESIZE(float,m_duration,Duration);//存活时间
public:
	Product();
	~Product();
	CREATE_FUNC(Product);
	bool init();

	void update(float dt);
};
#endif