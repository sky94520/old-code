#include "DoubleColumn.h"
#include "Column.h"

DoubleColumn::DoubleColumn()
	:m_pTop(nullptr),m_pBottom(nullptr)
{
}
DoubleColumn::~DoubleColumn()
{
}
bool DoubleColumn::init()
{
	this->reset();
	return true;
}
void DoubleColumn::reset()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//随机上面柱子长度
	int y1 = RANDOM(150,350);
	int y2 = visibleSize.height - y1 - 200;
	//设置上方柱子
	if(m_pTop == nullptr)
	{
		m_pTop = Column::create(y1,ColumnType::kColumn_Top);
		this->addChild(m_pTop);
	}
	else
		m_pTop->setLen(y1);
	//设置下方柱子
	if(m_pBottom == nullptr)
	{
		m_pBottom = Column::create(y2,ColumnType::kColumn_Bottom);
		this->addChild(m_pBottom);
	}
	else
		m_pBottom->setLen(y2);
}
bool DoubleColumn::isAvaiable()const
{
	//获取柱子宽度
	Size size = m_pTop->getContentSize();
	Point pos = this->getPosition();

	if(pos.x + size.width <= 0)
		return false;
	return true;
}
bool DoubleColumn::checkCollision(const Rect&rect)
{
	//判断上柱子
	Rect r1 = m_pTop->getBoundingBox();
	r1.origin = m_pTop->getWorldPosition();

	if(r1.intersectsRect(rect))
		return true;
	//下柱子
	Rect r2 = m_pBottom->getBoundingBox();
	r2.origin = m_pBottom->getWorldPosition();

	if(r2.intersectsRect(rect))
		return true;
	return false;
}