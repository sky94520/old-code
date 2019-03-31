#ifndef __ItemLayer_H__
#define __ItemLayer_H__
#include "cocos2d.h"
USING_NS_CC;
class DoubleBulletItem;
class GameLayerDelegate;
class ItemLayer:public Layer
{
private:
	DoubleBulletItem*m_pDoubleBulletItem;
public:
	ItemLayer();
	~ItemLayer();
	static ItemLayer*create(GameLayerDelegate*pDelegate);
	bool init(GameLayerDelegate*pDelegate);
	virtual void update(float dt);

	void showBulletItem();
};
#endif