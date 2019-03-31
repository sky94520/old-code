#ifndef __CsvData_H__
#define __CsvData_H__
#include "cocos2d.h"
USING_NS_CC;

class CsvData : public Ref
{
public:
	CREATE_FUNC(CsvData);
	virtual bool init();
	//���һ������
	void addLineData(ValueVector lineData);
	//��ȡĳ�е�����
	ValueVector getSingleLineData(int iLine);
	//��ȡ���д�С
	Size getRowColNum();
private:
	//���Csv�ļ�����������
	ValueVector m_allLinesVec;
	//int m_iColNum;
};
#endif