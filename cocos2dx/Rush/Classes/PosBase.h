#ifndef __PosBase_H__
#define __PosBase_H__
#include "cocos2d.h"
USING_NS_CC;
class PosBase:public Node
{
protected:
	bool m_bIsDebug;
public:
	PosBase();
	~PosBase();
	static PosBase*create(Point pos);
	static PosBase*create(Point pos,bool isDebug);
	bool init(Point pos);
	bool init(Point pos,bool isDebug);

	CC_SYNTHESIZE(Point,m_pos,Pos);
	//ÊÇ·ñµã»÷
	virtual bool isClickMe(Point pos);
	void setDebug(bool debug);
};
#endif