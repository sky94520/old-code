#include "PosBase.h"
PosBase::PosBase():m_bIsDebug(true)
{
}
PosBase::~PosBase()
{
}
PosBase*PosBase::create(Point pos)
{
	PosBase*tPos = new PosBase();
	if(tPos && tPos->init(pos))
	{
		tPos->autorelease();
		return tPos;
	}
	CC_SAFE_DELETE(tPos);
	return NULL;
}
PosBase*PosBase::create(Point pos,bool debug)
{
	PosBase*tPos = new PosBase();
	if(tPos && tPos->init(pos,debug))
	{
		tPos->autorelease();
		return tPos;
	}
	CC_SAFE_DELETE(tPos);
	return NULL;
}
bool PosBase::init(Point pos)
{
	setPos(pos);
	return true;
}
bool PosBase::init(Point pos,bool debug)
{
	setPos(pos);
	m_bIsDebug = debug;
	return true;
}
bool PosBase::isClickMe(Point pos)
{
	return true;
}
void PosBase::setDebug(bool debug)
{
	m_bIsDebug = debug;
}