#ifndef __Fork_H__
#define __Fork_H__
#include<vector>
#include "Entity.h"
class Fork : public Entity
{
private:
	bool m_bShooting;//当前鱼叉是否正在插鱼
	Point m_targetPos;//目标点
public:
	Fork();
	~Fork();
	CREATE_FUNC(Fork);
	bool init();
	//插鱼 targetPos 世界坐标
	void shoot(const Point&targetPos);
	//获取有效碰撞范围，为世界坐标
	virtual Rect getColliableRect()const;

	std::vector<Rect> getColliableRects()const;

	void setShooting(bool shooting);
	bool isShooting()const;
};
#endif