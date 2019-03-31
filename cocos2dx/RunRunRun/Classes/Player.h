#ifndef __Player_H__
#define __Player_H__

#include "Entity.h"

class Player : public Entity
{
public:
	CREATE_FUNC(Player);
	virtual bool init();

	void run();

	virtual void setTagPosition(int x,int y);
	void setTiledMap(TMXTiledMap*map);
private:
	void setViewPointByPlayer();
	//将像素坐标转换为地图格子坐标
	Point tileCoordForPosition(Point);

	TMXTiledMap*m_map;
	//检测碰撞的地图层
	TMXLayer*meta;
	//标记主角是否碰撞了障碍物，在反弹中
	bool isJumping;
};
#endif