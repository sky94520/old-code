#ifndef __PlayerLayer_H__
#define __PlayerLayer_H__
#include "SDL_Engine/SDL_Engine.h"
#include "KeyEventLayer.h"
#include "Bullet.h"

using namespace SDL;
class Player;
class Entity;
class PlayerLayerDelegate
{
public:
	virtual ~PlayerLayerDelegate(){}
	virtual Point getPlayerBornPos()const=0;//获取主角出生点
	virtual TMXLayer*getEntityLayer()const=0;//获取实体层
	virtual int isCollidedTileWithCollidedLayer(const Rect& r,char dir)const=0;
	virtual int isCollidedTileWithCollidedLayer(const Rect&r,Entity*entity,char dir)=0;
	virtual int isCollidedTileWithCoinLayer(const Rect&r,Entity*entity,char dir) = 0;
	//virtual int isCollidedTile(const Rect&r,Entity*entity,char dir)=0;
	virtual Point getGravity()const=0;
	virtual ValueMap getTilePropertiesForGID(int gid)=0;
	virtual void addPlayerBullet(BulletType bulletType,const Point&startPos,const Point&heading,const string&customName)=0;
};
class PlayerLayer:public Layer
{
private:
	Player*m_pPlayer;
	PlayerLayerDelegate*m_pDelegate;
	TMXLayer*m_pEntityLayer;
	float m_velocitys[2];//主角的两级最大速度
	float m_velocityPerSec;//每秒的速度增量，加速度
	Point m_lastSafePos;//安全点，死亡后的马里奥将在这个点复活
	float m_jumpHeight[2];
	float m_remantHeight;//剩余高度
	bool m_bCanJump;
	bool m_bJumpHigher;//是否已经跳得更高
	//处理各种按键
	bool m_bLeftPressed;
	bool m_bRightPressed;
	bool m_bJumpPressed;
	bool m_bShootPressed;
	bool m_bDownPressed;
public:
	PlayerLayer();
	~PlayerLayer();
	static PlayerLayer*create(PlayerLayerDelegate*pDelegate);

	bool init(PlayerLayerDelegate*pDelegate);
	virtual void update(float dt);
	//获取主角
	Player*getPlayer()const;
	virtual void keyPressed(EventType eventType);
	virtual void keyReleased(EventType eventType);
	//设置主角跳跃高度
	void setPlayerRemantHeight(int remantHeight);
	void addPlayerRemantHeight(int remantHeight);
private:
	void updateMarioVelocity(float dt);
	void playerLeft();
	void playerRight();
	void playerJump();
	void playerShoot();
	bool isPlayerOutside();
};
#endif