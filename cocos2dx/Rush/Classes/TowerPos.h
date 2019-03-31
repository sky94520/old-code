#ifndef __TowerPos_H__
#define __TowerPos_H__
#include "PosBase.h"
#define TOWER_RADIUS 32
class TowerPos : public PosBase
{
private:
	void onDraw(const kmMat4 &transform,bool transformUpdated);
	CustomCommand _customCommand;
public:
	TowerPos();
	~TowerPos();
	static TowerPos*create(Point pos);
	static TowerPos*create(Point pos,bool isDebug);
	bool init(Point pos);
	bool init(Point pos,bool isDebug);

	virtual void draw(Renderer*renderer,const kmMat4 &,uint32_t flags);

	virtual bool isClickMe(Point pos);
};
#endif