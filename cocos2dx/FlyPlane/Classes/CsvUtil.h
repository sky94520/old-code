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
	//加载配置文件
	void loadFile(const char*sPath);
	//获取某行某列的值
	Value getValue(int iRow,int iCol,const char*csvFilePath);
	//获取值并转化为字符串
	const std::string  get(int iRow,int iCol,const char*csvFilePath);
	//获取并转化为整型
	const int getInt(int iRow,int iCol,const char*csvFilePath);
	//获取文件的行列数
	const Size getFileRowColNum(const char*csvFilePath);
	//根据某个列的值，查找该值所在的行
	const int findValueInWithLine(const char*chValue,int iValueCol,const char*csvfilePath);
private:
	static CsvUtil*m_CsvUtil;
	//存放字典
	Map<std::string,CsvData*> mCsvMap;
};
#endif