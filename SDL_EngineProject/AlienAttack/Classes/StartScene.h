#ifndef __StartScene_H__
#define __StartScene_H__
#include<vector>
#include "SDL_Engine/SDL_Engine.h"
#include "StartMenuLayer.h"
#include "ShopLayer.h"

using namespace SDL;
using namespace std;
using namespace SDL::ui;
class ShopLayer;
class BackDelegate
{
public:
	virtual ~BackDelegate(){}
	virtual void backToStartMenuLayer()=0;
};
class StartScene:public Scene
	,public StartMenuLayerDelegate,public BackDelegate
{
private:
	StartMenuLayer*m_pStartMenuLayer;
	ShopLayer*m_pShopLayer;

	Layer*m_pActiveLayer;//当前活动层
public:
	StartScene();
	~StartScene();
	CREATE_FUNC(StartScene);
	bool init();
private:
	void selectActiveLayer(Layer*layer);//选中某一层作为活动层
private://delegate
	virtual void gameStart();
	virtual void gotoShop();
	virtual void gameExit();
	virtual void backToStartMenuLayer();
};
#endif