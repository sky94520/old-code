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
	kResult_None,//û�з�����ײ
	kResult_OnlyCollided,//������ײ����Ϸδ����
	kResult_GameOver //��Ϸ����
};
class MapLayer:public Layer
{
	SDL_SYNTHESIZE(Size,m_mapSize,MapSize);//�ߴ�
	SDL_SYNTHESIZE(Rect,m_clientRect,ClientRect);//�ͻ���
	SDL_SYNTHESIZE(Size,m_tileSize,TileSize);//�����С
private:
	Sprite*m_pMap[21][12];
public:
	MapLayer();
	~MapLayer();
	CREATE_FUNC(MapLayer);
	bool init();
	void update(float dt);

	bool isCollided(Brick*brick);//�Ƿ񷵻���ײ
	CollideResult isGameOver(Brick*brick);//��Ϸ�Ƿ����
	void insertBrick(Brick*brick);
	int clearUpBrick();//������飬���ط���
	void reset();
};
#endif