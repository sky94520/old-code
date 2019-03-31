#include "Column.h"
Column::Column()
{
}
Column::~Column()
{
}
Column*Column::create(unsigned int len,ColumnType type)
{
	auto column = new Column();
	if(column && column->init(len,type))
		column->autoRelease();
	else
		SDL_SAFE_DELETE(column);
	return column;
}
bool Column::init(unsigned int len,ColumnType type)
{
	m_nLen = len;
	m_type = type;
	//加载图片，同时设置y轴
	if(type == ColumnType::kColumn_Top)
	{
		bindSprite(Sprite::create("pic/column2.png"));
		Size s = this->getContentSize();
		auto y = len - s.height;
		this->setPositionY(y);
	}
	else if(type == ColumnType::kColumn_Bottom)
	{
		bindSprite(Sprite::create("pic/column1.png"));
		Size visibleSize = Director::getInstance()->getVisibleSize();

		auto y = visibleSize.height - len;
		this->setPositionY(y);
	}
	return true;
}
void Column::setLen(unsigned int len)
{
	if(len == m_nLen)
		return;
	m_nLen = len;
	//根据类型设置y坐标的高度
	if(m_type == ColumnType::kColumn_Top)
	{
		Size s = this->getContentSize();
		auto y = len - s.height;
		this->setPositionY(y);
	}
	else if(m_type == ColumnType::kColumn_Bottom)
	{
		Size visibleSize = Director::getInstance()->getVisibleSize();

		auto y = visibleSize.height - len;
		this->setPositionY(y);
	}
}