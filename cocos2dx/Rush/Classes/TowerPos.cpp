#include "TowerPos.h"
TowerPos::TowerPos()
{
}
TowerPos::~TowerPos()
{
}
bool TowerPos::init(Point pos)
{
	if(!PosBase::init(pos))
		return false;
	return true;
}
bool TowerPos::init(Point pos,bool isDebug)
{
	if(!PosBase::init(pos,isDebug))
		return false;
	return true;
}
TowerPos*TowerPos::create(Point pos)
{
	TowerPos*tPos = new TowerPos();
	if(tPos && tPos->init(pos))
	{
		tPos->autorelease();
		return tPos;
	}
	CC_SAFE_DELETE(tPos);
	return NULL;
}
TowerPos*TowerPos::create(Point pos,bool isDebug)
{
	TowerPos*tPos = new TowerPos();
	if(tPos && tPos->init(pos,isDebug))
	{
		tPos->autorelease();
		return tPos;
	}
	CC_SAFE_DELETE(tPos);
	return NULL;
}
void TowerPos::onDraw(const kmMat4 &transform,bool transformUpdated)
{
	kmGLPushMatrix();
	kmGLLoadMatrix(&transform);
	//ÉèÖÃ»­±Ê´ÖÏ¸
	glLineWidth(5.f);
	//»æÖÆ¾ØÐÎ
	Point srcPos = Point(m_pos.x - TOWER_RADIUS,m_pos.y + TOWER_RADIUS);
	Point destPos = Point(m_pos.x + TOWER_RADIUS,m_pos.y - TOWER_RADIUS);
	DrawPrimitives::drawRect(srcPos,destPos);
	glLineWidth(1);
	//½áÊø»æÖÆ
	kmGLPopMatrix();
}
void TowerPos::draw(Renderer*renderer,const kmMat4 &transform,uint32_t flags)
{
	if(m_bIsDebug)
	{
		_customCommand.init(_globalZOrder);
		_customCommand.func = CC_CALLBACK_0(TowerPos::onDraw,this,transform,flags);
		renderer->addCommand(&_customCommand);
	}
}
bool TowerPos::isClickMe(Point pos)
{
	Point srcPos = Point(m_pos.x - TOWER_RADIUS,m_pos.y + TOWER_RADIUS);
	Point destPos = Point(m_pos.x + TOWER_RADIUS,m_pos.y - TOWER_RADIUS);
	if(pos.x >= srcPos.x && pos.x <= destPos.x && pos.y >= destPos.y && pos.y <= srcPos.y)
		return true;
	return false;
}