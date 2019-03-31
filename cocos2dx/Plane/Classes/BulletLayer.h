#ifndef __BulletLayer_H__
#define __BulletLayer_H__
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "SystemHeader.h"
USING_NS_CC;
class BulletLayerDelegate
{
public:
	virtual ~BulletLayerDelegate(){}
	virtual void shootTo(const Vec2&startPos)=0;
	virtual void bindPhysicalBody(void*userdata,const MyBody&myBody,b2Shape*shape)=0;
};
class Bullet;
class BulletLayer:public Layer
{
private:
	std::vector<Bullet*> m_bulletList;
	BulletType m_bulletType;//当前子弹类型
	BulletLayerDelegate*m_pDelegate;
public:
	BulletLayer();
	~BulletLayer();
	bool init();
	CREATE_FUNC(BulletLayer);
	void shootTo(const Point&startPos);
	void setBulletType(Ref*sender);

	void setDelegate(BulletLayerDelegate*pDelegate);
private:
	void shoot(const Point&startPos);
};
#endif