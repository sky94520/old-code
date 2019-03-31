#include "MonsterPos.h"
MonsterPos::MonsterPos()
{
}
MonsterPos::~MonsterPos()
{
}
bool MonsterPos::init(Point pos)
{
	if(!PosBase::init(pos))
		return false;
	return true;
}
bool MonsterPos::init(Point pos,bool isDebug)
{
	if(!PosBase::init(pos,isDebug))
		return false;
	return true;
}
MonsterPos*MonsterPos::create(Point pos)
{
	MonsterPos*tPos = new MonsterPos();
	if(tPos && tPos->init(pos))
	{
		tPos->autorelease();
		return tPos;
	}
	CC_SAFE_DELETE(tPos);
	return NULL;
}
MonsterPos*MonsterPos::create(Point pos,bool isDebug)
{
	MonsterPos*tPos = new MonsterPos();
	if(tPos && tPos->init(pos,isDebug))
	{
		tPos->autorelease();
		return tPos;
	}
	CC_SAFE_DELETE(tPos);
	return NULL;
}
void MonsterPos::onDraw(const kmMat4 &transform,bool transformUpdated)
{
	kmGLPushMatrix();
	kmGLLoadMatrix(&transform);
	//ÉèÖÃ»­±Ê´ÖÏ¸
	glLineWidth(4.f);
	//»æÖÆÔ²ÐÎ
	DrawPrimitives::drawCircle(m_pos,MONSTER_RADIUS,360,20,false);
	glLineWidth(1);
	//½áÊø»æÖÆ
	kmGLPopMatrix();
}
void MonsterPos::draw(Renderer*renderer,const kmMat4 &transform,uint32_t flags)
{
	if(m_bIsDebug)
	{
		_customCommand.init(_globalZOrder);
		_customCommand.func = CC_CALLBACK_0(MonsterPos::onDraw,this,transform,flags);
		renderer->addCommand(&_customCommand);
	}
}
bool MonsterPos::isClickMe(Point pos)
{
	Point srcPos = Point(m_pos.x - MONSTER_RADIUS,m_pos.y + MONSTER_RADIUS);
	Point destPos = Point(m_pos.x + MONSTER_RADIUS,m_pos.y - MONSTER_RADIUS);
	if(pos.x >= srcPos.x && pos.x <= destPos.x && pos.y >= destPos.y && pos.y <= srcPos.y)
		return true;
	return false;
}