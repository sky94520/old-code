#include "Command.h"
#include "Brick.h"

LeftCommand::LeftCommand(Brick*pBrick)
	:m_pBrick(pBrick)
{
}
void LeftCommand::execute()
{
	Size s = m_pBrick->getTileSize();
	m_prePosition = m_pBrick->getPosition();

	Point nextPos = m_prePosition - Point(s.width,0);
	m_pBrick->setPosition(nextPos);
}
void LeftCommand::undo()
{
	m_pBrick->setPosition(m_prePosition);
}
//---------------------------RightCommand------------------------
RightCommand::RightCommand(Brick*pBrick)
	:m_pBrick(pBrick)
{
}
void RightCommand::execute()
{
	Size s = m_pBrick->getTileSize();
	m_prePosition = m_pBrick->getPosition();

	Point nextPos = m_prePosition + Point(s.width,0);
	m_pBrick->setPosition(nextPos);
}
void RightCommand::undo()
{
	m_pBrick->setPosition(m_prePosition);
}
//--------------------------TransformCommand----------------------
TransformCommand::TransformCommand(Brick*pBrick)
	:m_pBrick(pBrick),m_nPreIndex(0)
{
}
void TransformCommand::execute()
{
	const auto& shapes = m_pBrick->m_shapes;
	int curIndex =m_nPreIndex = m_pBrick->m_nCurIndex;

	curIndex = (curIndex+1)%shapes.size();
	m_pBrick->m_nCurIndex = curIndex;

	Shape shape = shapes.at(curIndex);
	for(int i=0;i<4;i++)
	{
		Node*node = m_pBrick->getChildByTag(i);
		Point point = shape.p[i];
		Size s = node->getContentSize();
		node->setPosition(point.x*s.width,point.y*s.height);
	}
}
void TransformCommand::undo()
{
	m_pBrick->m_nCurIndex = m_nPreIndex;
	vector<Shape> &shapes = m_pBrick->m_shapes;
	Shape&shape = shapes.at(m_nPreIndex);

	for(int i=0;i<4;i++)
	{
		Node*node = m_pBrick->getChildByTag(i);
		Point point = shape.p[i];
		Size s = node->getContentSize();
		node->setPosition(point.x*s.width,point.y*s.height);
	}
}