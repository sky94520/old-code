#include "ArrowAction.h"
ArrowAction::ArrowAction()
{
}
ArrowAction::~ArrowAction()
{
}
ArrowAction*ArrowAction::create(const Vec2&startPos,const Vec2&middle)
{
	auto action = new ArrowAction();
	if(action && action->init(startPos,middle))
		action->autorelease();
	else
		CC_SAFE_DELETE(action);
	return action;
}
bool ArrowAction::init(const Vec2&startPos,const Vec2&middle)
{
	//ȷ����������
	Vec2 endPos = Vec2(2*middle.x-startPos.x,startPos.y);
	//��ֵ
	_arrowConfig.startPos = startPos;
	_arrowConfig.middlePos = middle;
	_arrowConfig.endPos = endPos;
	//ȷ������
	return true;
}