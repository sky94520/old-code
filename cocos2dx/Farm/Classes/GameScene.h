#ifndef __GameScene_H__
#define __GameScene_H__
#include "cocos2d.h"
#include "TouchLayer.h"
#include "MapLayer.h"
#include "ShopLayer.h"

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

using namespace ui;
using namespace cocostudio;

USING_NS_CC;
class GameScene:public Scene,public TouchLayerDelegate
{
private:
	TouchLayer*m_pTouchLayer;//事件分发层
	MapLayer*m_pMapLayer;
	ShopLayer*m_pShopLayer;
	ProgressTimer*m_pProgress;
public:
	GameScene();
	~GameScene();
	CREATE_FUNC(GameScene);
	bool init();
private:
	virtual void operateBackground(const std::vector<Touch*>&touches,Event*event);
	//win linux下设置缩放
	virtual void setScaleForBackground(EventMouse*event);
	virtual void update(float dt);
};
#endif