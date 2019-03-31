#ifndef __CsvData_H__
#define __CsvData_H__
#include "cocos2d.h"
USING_NS_CC;
class CsvData : public Ref
{
private:
	ValueVector m_allData;
public:
	CREATE_FUNC(CsvData);
	virtual bool init();
	//获得行列大小
	Size getRowColNum();
	//增加行
	void addLineData(ValueVector lineVector);
	//获得行数据
	ValueVector getSingleLineData(int row);
};
#endif