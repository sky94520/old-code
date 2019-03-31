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
	//Ŀǰ�����һ��
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
		//���ã�������������
		if(c->isAvaiable())
		{
			c->setPositionX(c->getPositionX() - m_speed);
		}
		else
		{
			//�����ڲ����ӳ���
			c->reset();
			//��������λ��
			Size visibleSize = Director::getInstance()->getVisibleSize();
			c->setPositionX(visibleSize.width);
		}
	}
}
vector<DoubleColumn*>& ColumnLayer::getColumns()
{
	return m_columns;
}