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
//��ײ��ͼ��ص�����
typedef function<int (TMXLayer*layer,const Point&tileCoordinate)> TileCollidedCallback;

class MapLayer:public Layer
{
private:
	TMXTiledMap*m_pTiledMap;
	//��m_pTiledMap��tiled object layer�ļ�����
	vector<TMXObject*> m_tileObjects;
	vector<TMXObject*> m_entityObjects;

	MapLayerDelegate*m_pDelegate;
public:
	MapLayer();
	~MapLayer();
	CREATE_FUNC(MapLayer);
	bool init();
	void update(float dt,Player*player);
	//��ȡ��ɫ������
	Point getPlayerBornPos()const;
	//�Ƿ�Ͷ�Ӧ��tmx�㷢����ײ������ص��������ڣ��ͻص��������������������ص������ķ���ֵ
	int isCollidedTile(const Rect&r,char dir,TMXLayer*layer,const TileCollidedCallback&callback = nullptr);
	//��ȡtiled map
	TMXTiledMap*getTMXTiledMap()const;
	void setDelegate(MapLayerDelegate*pDelegate);

	int entityInteractWithTile(Entity*entity,TMXLayer*layer,const Point&tileCoordinate);
	//�����Ż��������꣬����Ż��ɹ����򲻽���ͼ����ײ
	bool optimizePlayerPos(Player*player,Sprite*tileSprite);
};
#endif