#ifndef __CsvUtil_H__
#define __csvUtil_H__
#include<fstream>
#include<map>
#include<algorithm>
#include "cocos2d.h"
class CsvData;
USING_NS_CC;
class CsvUtil:public Ref
{
private:
	std::map<std::string,CsvData*> m_allCsvData;
	static CsvUtil*m_pInstance;
	CsvUtil();
	~CsvUtil();
public:
	static CsvUtil*getInstance();
	void destroyInstance();
	void purge();
	CsvData* loadFile(const char*fileName);
	//����кź��к�
	Size getRowColNum(std::string name);
	//�������
	Value getValue(int nRow,int nCol,const std::string&fileName);
	//�ҵ��������ڵ�����
	int findLineByValue(Value value,int column,std::string fileName);

};
#endif