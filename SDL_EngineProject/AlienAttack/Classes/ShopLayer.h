#ifndef __ShopLayer_H__
#define __ShopLayer_H__
#include<string>
#include "SDL_Engine/SDL_Engine.h"
using namespace std;
using namespace SDL;
using namespace SDL::ui;

class BackDelegate;
class ShopLayer:public Layer
{
private:
	BackDelegate*m_pDelegate;
public:
	ShopLayer();
	~ShopLayer();
	CREATE_FUNC(ShopLayer);
	bool init();
	void setDelegate(BackDelegate*pDelegate);
private:
	void back(Object*sender);
	void updateStatusOfWidget(Node*parent);
	void buyCallback(Object*sender);//¹ºÂò»Øµ÷º¯Êý
};
#endif