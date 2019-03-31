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
	/*���̫��
	*number ̫���ĸ��� Ӱ��̫���Ĵ�С Ŀǰ25 Ϊ���� 15ΪС
	*action ̫���ĳ�������
	*/
	void makeSun(int number,FiniteTimeAction*action,const Point&bornPos,Layer*layer);
	//��ȡ����˵�product
	Product*getClickedProduct(const Point&pos);
};
#endif