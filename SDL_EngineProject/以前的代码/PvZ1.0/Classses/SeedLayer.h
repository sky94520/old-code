#ifndef __SeedLayer_H__
#define __SeedLayer_H__
#include<vector>
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;
class Seed;
class SeedLayer:public Node
{
private:
	int m_selectedIndex;//当前选中项
	Vector<Seed*> m_seeds;//种子包
	Sprite*m_pSelectedHigh;//选中高亮
public:
	SeedLayer();
	~SeedLayer();
	CREATE_FUNC(SeedLayer);
	bool init();
	virtual void update(float dt);
	//添加种子包
	bool addSeed(const std::string &name);
	//移除种子包
	void removeSeed(const std::string &name);
	//设置当前选中项，若无操作返回false
	bool setSelectedSeed(const Point&pos);
	//获取当前选中的种子包
	Seed*getSelectedSeed();
	//清除选中
	void clearClickHigh();
private:
	Seed*getItemForTouch(Touch*touch);
};
#endif