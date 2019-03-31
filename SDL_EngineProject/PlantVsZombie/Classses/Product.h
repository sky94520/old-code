#ifndef __Product_H__
#define __Product_H__

#include "SDL_Engine/SDL_Engine.h"
#include "Entity.h"

using namespace SDL;

enum class ProductType
{
	None,
	Sun,//̫��
	Gold,//���
};

class Product:public Entity
{
	SDL_SYNTHESIZE(ProductType,m_productType,ProductType);
	SDL_SYNTHESIZE(int,m_nNumber,Number);
	SDL_BOOL_SYNTHESIZE(m_bClicked,Clicked);//�Ƿ��Ѿ����
	SDL_BOOL_SYNTHESIZE(m_bUpdate,Update);//�Ƿ�ʼ����
	SDL_BOOL_SYNTHESIZE(m_bDead,Dead);//�Ƿ�����
	SDL_SYNTHESIZE(float,m_duration,Duration);//���ʱ��
public:
	Product();
	~Product();
	CREATE_FUNC(Product);
	bool init();

	void update(float dt);
};
#endif