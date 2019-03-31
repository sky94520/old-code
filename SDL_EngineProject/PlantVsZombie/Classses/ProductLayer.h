#ifndef __ProductLayer_H__
#define __ProductLayer_H__
#include<vector>
#include "SDL_Engine/SDL_Engine.h"
using namespace std;
using namespace SDL;
class Product;

class ProductLayer : public Layer
{
private:
	vector<Product*> m_products;
public:
	ProductLayer();
	~ProductLayer();
	CREATE_FUNC(ProductLayer);
	bool init();

	void update(float dt);
	/*添加太阳
	*number 太阳的个数 影响太阳的大小 目前25 为正好 15为小
	*action 太阳的出生动画
	*/
	void makeSun(int number,FiniteTimeAction*action,const Point&bornPos,Layer*layer);
	//获取点击了的product
	Product*getClickedProduct(const Point&pos);
};
#endif