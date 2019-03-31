#ifndef __MonsterPos_H__
#define __MonsterPos_H__
#include "PosBase.h"
#define MONSTER_RADIUS 10
class MonsterPos : public PosBase
{
private:
	void onDraw(const kmMat4 &transform,bool transformUpdated);
	CustomCommand _customCommand;
public:
	MonsterPos();          
	~MonsterPos();
	static MonsterPos*create(Point pos);
	static MonsterPos*create(Point pos,bool isDebug);
	bool init(Point pos);
	bool init(Point pos,bool isDebug);

	virtual void draw(Renderer*renderer,const kmMat4 &,uint32_t flags);

	virtual bool isClickMe(Point pos);
};
#endif