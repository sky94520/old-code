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
	bool m_bRightPressed;
	bool m_bLeftPressed;

	PlayerLayerDelegate*m_pDelegate;
public:
	PlayerLayer();
	~PlayerLayer();
	CREATE_FUNC(PlayerLayer);
	bool init();
	virtual void update(float dt);
	//对主角进行操作
	void onKeyPressed(SDL_Keycode,SDL_Event*);
	void onKeyReleased(SDL_Keycode,SDL_Event*);

	 Plane*getPlayer()const;
	 void setDelegate(PlayerLayerDelegate*pDelegate);
	 void reset();
private:
	 void playerRevive();//主角重生

	void bindPhysicalPlane(Plane*plane);

	virtual void shooting(Plane*plane,BulletType type);
};
#endif