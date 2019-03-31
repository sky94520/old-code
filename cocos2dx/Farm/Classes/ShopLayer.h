#ifndef __ShopLayer_H__
#define __ShopLayer_H__
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio;

class MapLayer;
/*商店界面：
1.csb
2.能购买商店，并能放到地图中*/
class ShopLayer:public Layer
{
	CC_SYNTHESIZE(MapLayer*,m_pMapLayer,MapLayer);
private:
	Node*m_pShop;//csb
	bool m_bShowingShop;//是否正在显示商店
	Sprite*m_pBuyTarget;
	bool m_bCanBuy;//商品是否可以购买

	Point m_curPos;
	Point m_prePos;
public:
	ShopLayer();
	~ShopLayer();
	CREATE_FUNC(ShopLayer);
	bool init();

	void showShop(Ref*);
	void buy(Ref*,Widget::TouchEventType);

	Point convertToTiledCoord(const Point&position);
	Point convertToScreenCoord(const Point&position);
	void moveCheck(const Point&pos,String*item);
};
#endif