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

	Point m_gravity;//重力
public:
	GameScene();
	~GameScene();
	CREATE_FUNC(GameScene);
	bool init();
	virtual void update(float dt);
	//获取实体层
	TMXLayer*getEntityLayer()const;
	TMXLayer*getCollidedLayer()const;
	TMXLayer*getCoinLayer()const;
	Player*getPlayer()const;
	//加载关卡
	void loadLevel();
public:
	virtual Point getGravity()const;
	ValueMap getTilePropertiesForGID(int gid);
	//对MapLayer的isCollidedTile的再次封装 碰撞图块层
	int isCollidedTileWithCollidedLayer(const Rect&r,char dir)const;
	int isCollidedTileWithCollidedLayer(const Rect&r,Entity*entity,char dir);
	//金币层
	int isCollidedTileWithCoinLayer(const Rect&r,char dir);
	int isCollidedTileWithCoinLayer(const Rect&r,Entity*entity,char dir);
	//一些特效
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
	//地图碰撞函数
	int collidedWithBlockCallback(TMXLayer*layer,const Point&tileCoordinate,Entity*entity);
	int collidedWithCoinCallback(TMXLayer*layer,const Point&tileCoordinate,Entity*entity);
	//定时回调函数 减少时间
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