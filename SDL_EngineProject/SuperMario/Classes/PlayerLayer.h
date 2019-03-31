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
	virtual Point getPlayerBornPos()const=0;//��ȡ���ǳ�����
	virtual TMXLayer*getEntityLayer()const=0;//��ȡʵ���
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
	float m_velocitys[2];//���ǵ���������ٶ�
	float m_velocityPerSec;//ÿ����ٶ����������ٶ�
	Point m_lastSafePos;//��ȫ�㣬�����������½�������㸴��
	float m_jumpHeight[2];
	float m_remantHeight;//ʣ��߶�
	bool m_bCanJump;
	bool m_bJumpHigher;//�Ƿ��Ѿ����ø���
	//������ְ���
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
	//��ȡ����
	Player*getPlayer()const;
	virtual void keyPressed(EventType eventType);
	virtual void keyReleased(EventType eventType);
	//����������Ծ�߶�
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