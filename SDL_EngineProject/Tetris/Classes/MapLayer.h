#ifndef __MapLayer_H__
#define __MapLayer_H__
#include<string>
#include<algorithm>
#include "SDL_Engine/SDL_Engine.h"
#include "SDL_gfx.h"

class Brick;
using namespace SDL;
using namespace std;
enum CollideResult
{
	kResult_None,//没有发生碰撞
	kResult_OnlyCollided,//发生碰撞但游戏未结束
	kResult_GameOver //游戏结束
};
class MapLayer:public Layer
{
	SDL_SYNTHESIZE(Size,m_mapSize,MapSize);//尺寸
	SDL_SYNTHESIZE(Rect,m_clientRect,ClientRect);//客户区
	SDL_SYNTHESIZE(Size,m_tileSize,TileSize);//方块大小
private:
	Sprite*m_pMap[21][12];
public:
	MapLayer();
	~MapLayer();
	CREATE_FUNC(MapLayer);
	bool init();
	void update(float dt);

	bool isCollided(Brick*brick);//是否返回碰撞
	CollideResult isGameOver(Brick*brick);//游戏是否结束
	void insertBrick(Brick*brick);
	int clearUpBrick();//清除方块，返回分数
	void reset();
};
#endif