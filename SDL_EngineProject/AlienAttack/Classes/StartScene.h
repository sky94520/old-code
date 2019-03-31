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

	Layer*m_pActiveLayer;//��ǰ���
public:
	StartScene();
	~StartScene();
	CREATE_FUNC(StartScene);
	bool init();
private:
	void selectActiveLayer(Layer*layer);//ѡ��ĳһ����Ϊ���
private://delegate
	virtual void gameStart();
	virtual void gotoShop();
	virtual void gameExit();
	virtual void backToStartMenuLayer();
};
#endif