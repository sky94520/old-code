#ifndef __PlayerLayer_H__
#define __PlayerLayer_H__
#include "SDL_Engine/SDL_Engine.h"
#include "Plane.h"

using namespace SDL;
class Player;
class PlayerLayerDelegate
{
public:
	virtual ~PlayerLayerDelegate(){}
	virtual void gameEnd()=0;
	virtual void shooting(Plane*plane,BulletType type) = 0;
};
class PlayerLayer:public Layer,public PlaneDelegate
{
private:
	Player*m_pPlayer;
	bool m_bAdjustPos;//是否调整飞机位置
	float m_endAngle;
	PlayerLayerDelegate*m_pDelegate;
public:
	PlayerLayer();
	~PlayerLayer();
	CREATE_FUNC(PlayerLayer);
	bool init();
	virtual void update(float dt);
	//对主角进行操作
	void degreeUpdate(const Point&degree);
	void wantShooting();

	 Plane*getPlayer()const;
	 void setDelegate(PlayerLayerDelegate*pDelegate);
	 void reset();
private:
	void bindPhysicalPlane(Plane*plane);

	virtual void shooting(Plane*plane,BulletType type);
};
#endif
