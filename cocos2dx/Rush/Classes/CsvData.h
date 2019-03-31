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
	//������д�С
	Size getRowColNum();
	//������
	void addLineData(ValueVector lineVector);
	//���������
	ValueVector getSingleLineData(int row);
};
#endif