#ifndef __CsvUtil_H__
#define __csvUtil_H__
#include<fstream>
#include "cocos2d.h"
class CsvData;
USING_NS_CC;
class CsvUtil
{
private:
	Map<std::string,CsvData*> m_allCsvData;
	static CsvUtil*m_pInstance;
	CsvUtil();
	~CsvUtil();
public:
	static CsvUtil*getInstance();
	CsvData* loadFile(const char*fileName);
	//����кź��к�
	Size getRowColNum(std::string name);
	//�������
	Value getValue(int nRow,int nCol,const char*fileName);
	//�ҵ��������ڵ�����
	int findLineByValue(Value value,int column,std::string fileName);
};
#endif