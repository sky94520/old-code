#ifndef __GameScene_H__
#define __GameScene_H__
#include<functional>

#include "SDL_Engine/SDL_Engine.h"
#include "PlayerLayer.h"
#include "KeyEventLayer.h"
#include "MapLayer.h"
#include "ItemLayer.h"
#include "EnemyLayer.h"
#include "BulletLayer.h"
#include "Bullet.h"

using namespace std;
using namespace SDL;
class Entity;
class Player;
class PanelLayer;

class GameScene:public Scene
	,public PlayerLayerDelegate,public EventLayerDelegate,public MapLayerDelegate
	,public ItemLayerDelegate,public EnemyDelegate,public BulletLayerDelegate
{
private:
	MapLayer*m_pMapLayer;
	PlayerLayer*m_pPlayerLayer;
	KeyEventLayer*m_pEventLayer;
	ItemLayer*m_pItemLayer;
	BulletLayer*m_pBulletLayer;
	EnemyLayer*m_pEnemyLayer;
	PanelLayer*m_pPanelLayer;

	Point m_gravity;//����
public:
	GameScene();
	~GameScene();
	CREATE_FUNC(GameScene);
	bool init();
	virtual void update(float dt);
	//��ȡʵ���
	TMXLayer*getEntityLayer()const;
	TMXLayer*getCollidedLayer()const;
	TMXLayer*getCoinLayer()const;
	Player*getPlayer()const;
	//���عؿ�
	void loadLevel();
public:
	virtual Point getGravity()const;
	ValueMap getTilePropertiesForGID(int gid);
	//��MapLayer��isCollidedTile���ٴη�װ ��ײͼ���
	int isCollidedTileWithCollidedLayer(const Rect&r,char dir)const;
	int isCollidedTileWithCollidedLayer(const Rect&r,Entity*entity,char dir);
	//��Ҳ�
	int isCollidedTileWithCoinLayer(const Rect&r,char dir);
	int isCollidedTileWithCoinLayer(const Rect&r,Entity*entity,char dir);
	//һЩ��Ч
	void goldAction(const Point&position);
	void blockBrokenAction(Sprite*sprite);
	void flowTextAction(const string&text,const Point&position);
	//PanelLayer
	void addCoin(int coin,Node*node=nullptr);
	void addScore(int score,Node*node=nullptr);

	void alterRemantTime(int time);
	void alterLife(int life);
private:
	void handleCollision(float dt);
	void handleCollisionBetweenPlayerAndItems(float dt);
	void handleCollisionBetweenPlayerAndEnemys(float dt);
	void handleCollisionBullets(float dt);
	//��ͼ��ײ����
	int collidedWithBlockCallback(TMXLayer*layer,const Point&tileCoordinate,Entity*entity);
	int collidedWithCoinCallback(TMXLayer*layer,const Point&tileCoordinate,Entity*entity);
	//��ʱ�ص����� ����ʱ��
	void reduceTime(float dt);
private://delegate
	virtual Point getPlayerBornPos()const;
	virtual void keyPressed(EventType eventType);
	virtual void keyReleased(EventType eventType);
	virtual bool createObjectByTypeAndName(TMXObject*object);
	virtual void createEntityByTMXObject(TMXObject*object);
	virtual void addPlayerBullet(BulletType bulletType,const Point&startPos,const Point&heading,const string&customName);
	virtual int collidedConsumeable(const ValueMap&properties,const Point&tileCoordinate,TMXLayer*layer);
	virtual void blockUpCallback(Sprite*tileSprite);
};
#endif