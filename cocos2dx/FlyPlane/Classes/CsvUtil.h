#ifndef __CsvUtil_H__
#define __CsvUtil_H__
#include "cocos2d.h"
#include "CsvData.h"
USING_NS_CC;

class CsvUtil : public Ref
{
public:
	static CsvUtil*getInstance();
	virtual bool init();
	//���������ļ�
	void loadFile(const char*sPath);
	//��ȡĳ��ĳ�е�ֵ
	Value getValue(int iRow,int iCol,const char*csvFilePath);
	//��ȡֵ��ת��Ϊ�ַ���
	const std::string  get(int iRow,int iCol,const char*csvFilePath);
	//��ȡ��ת��Ϊ����
	const int getInt(int iRow,int iCol,const char*csvFilePath);
	//��ȡ�ļ���������
	const Size getFileRowColNum(const char*csvFilePath);
	//����ĳ���е�ֵ�����Ҹ�ֵ���ڵ���
	const int findValueInWithLine(const char*chValue,int iValueCol,const char*csvfilePath);
private:
	static CsvUtil*m_CsvUtil;
	//����ֵ�
	Map<std::string,CsvData*> mCsvMap;
};
#endif