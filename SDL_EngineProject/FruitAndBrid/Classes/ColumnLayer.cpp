#include "ColumnLayer.h"
#include "DoubleColumn.h"

ColumnLayer::ColumnLayer()
	:m_speed(1.f)
{
}
ColumnLayer::~ColumnLayer()
{
}
bool ColumnLayer::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//目前仅添加一个
	DoubleColumn*c1 = DoubleColumn::create();
	c1->setPositionX(visibleSize.width);

	m_columns.push_back(c1);
	this->addChild(c1);

	return true;
}
void ColumnLayer::update(float dt)
{
	for(auto c:m_columns)
	{
		//可用，则进行坐标更新
		if(c->isAvaiable())
		{
			c->setPositionX(c->getPositionX() - m_speed);
		}
		else
		{
			//重置内部柱子长度
			c->reset();
			//重置柱子位置
			Size visibleSize = Director::getInstance()->getVisibleSize();
			c->setPositionX(visibleSize.width);
		}
	}
}
vector<DoubleColumn*>& ColumnLayer::getColumns()
{
	return m_columns;
}