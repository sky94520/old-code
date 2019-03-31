#ifndef __BrickLayer_H__
#define __BrickLayer_H__
#include<string>
#include<vector>
#include "SDL_Engine/SDL_Engine.h"
#include "MapLayer.h"
#include "Brick.h"

using namespace SDL;
using namespace std;

class Brick;
typedef struct
{
	string spriteName;
	vector<Shape> shapes;
}Block;
//��MapLayerͨ��
class BrickLayerDelegate
{
public:
	virtual ~BrickLayerDelegate(){}
	virtual Rect getClientRect()const=0;
	virtual bool isCollided(Brick*brick)=0;
	virtual CollideResult isGameOver(Brick*brick)=0;
	virtual void insertBrick(Brick*brick)=0;
	virtual int clearUpLineNum()=0;
	virtual void gameOver()=0;
};
class BrickLayer:public Layer
{
private:
	Brick*m_pNowBrick;
	Brick*m_pNextBrick;
	BrickLayerDelegate*m_pDelegate;
	vector<Block> m_blocks;
	float m_elpased;//�ӳ�
	float m_interval;//���
public:
	BrickLayer();
	~BrickLayer();
	static BrickLayer*create(BrickLayerDelegate*pDelegate);
	bool init(BrickLayerDelegate*pDelegate);

	virtual void update(float dt);
	virtual void onKeyPressed(SDL_Keycode keyCode,SDL_Event*event);
	void reset();
private:
	Brick*getRandomBrick();//������ɷ���

	bool left();
	bool right();
	bool transform();
	void initBlockS();//��ʼ������
	void initBlockO();
	void initBlockZ();
	void initBlockI();
	void initBlockL();
	void initBlockJ();
	void initBlockT();
};
#endif