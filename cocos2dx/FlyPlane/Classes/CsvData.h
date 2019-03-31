#ifndef __CsvData_H__
#define __CsvData_H__
#include "cocos2d.h"
USING_NS_CC;

class CsvData : public Ref
{
public:
	CREATE_FUNC(CsvData);
	virtual bool init();
	//添加一行数据
	void addLineData(ValueVector lineData);
	//获取某行的数据
	ValueVector getSingleLineData(int iLine);
	//获取行列大小
	Size getRowColNum();
private:
	//存放Csv文件的所有数据
	ValueVector m_allLinesVec;
	//int m_iColNum;
};
#endif