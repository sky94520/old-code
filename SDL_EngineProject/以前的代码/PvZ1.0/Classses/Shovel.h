#ifndef __Shovel_H__
#define __Shovel_H__
#include "SDL_Engine/SDL_Engine.h"
#include "Shovel.h"
using namespace SDL;
class Shovel : public Node
{
private:
	Sprite*m_pBackground;//背景
	Sprite*m_pSprite;//铲子
	//选中?
	bool m_bSelected;
public:
	Shovel();
	~Shovel();
	CREATE_FUNC(Shovel);
	bool init();
	//重置
	void clear();
	//是否选中
	bool isSelected()const;
	void setSelected(bool seleced);
	Sprite* getSprite()const;

	
	void runBlinkAction();
	void runKillPlantAction(const Point&pos);//坐标为世界坐标
};
#endif