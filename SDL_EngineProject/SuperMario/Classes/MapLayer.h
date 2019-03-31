#ifndef __MapLayer_H__
#define __MapLayer_H__
#include<vector>
#include<string>
#include<cmath>
#include<functional>

#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;
using namespace std;
class Player;
class Entity;
class MapLayerDelegate
{
public:
	virtual ~MapLayerDelegate(){}
	virtual bool createObjectByTypeAndName(TMXObject*object)=0;
	virtual void createEntityByTMXObject(TMXObject*object)=0;
	virtual int collidedConsumeable(const ValueMap&properties,const Point&tileCoordinate,TMXLayer*layer)=0;
	virtual void blockUpCallback(Sprite*tileSprite)=0;
	virtual void blockBrokenAction(Sprite*sprite)=0;
};
//碰撞到图块回调函数
typedef function<int (TMXLayer*layer,const Point&tileCoordinate)> TileCollidedCallback;

class MapLayer:public Layer
{
private:
	TMXTiledMap*m_pTiledMap;
	//对m_pTiledMap的tiled object layer的简单引用
	vector<TMXObject*> m_tileObjects;
	vector<TMXObject*> m_entityObjects;

	MapLayerDelegate*m_pDelegate;
public:
	MapLayer();
	~MapLayer();
	CREATE_FUNC(MapLayer);
	bool init();
	void update(float dt,Player*player);
	//获取角色出生点
	Point getPlayerBornPos()const;
	//是否和对应的tmx层发生碰撞，如果回调函数存在，就回调这个函数，并返回这个回调函数的返回值
	int isCollidedTile(const Rect&r,char dir,TMXLayer*layer,const TileCollidedCallback&callback = nullptr);
	//获取tiled map
	TMXTiledMap*getTMXTiledMap()const;
	void setDelegate(MapLayerDelegate*pDelegate);

	int entityInteractWithTile(Entity*entity,TMXLayer*layer,const Point&tileCoordinate);
	//尝试优化主角坐标，如果优化成功，则不进行图块碰撞
	bool optimizePlayerPos(Player*player,Sprite*tileSprite);
};
#endif