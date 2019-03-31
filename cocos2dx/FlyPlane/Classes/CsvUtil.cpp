#include "CsvUtil.h"
#include "StringUtil.h"

CsvUtil*CsvUtil::m_CsvUtil = NULL;

CsvUtil*CsvUtil::getInstance()
{
	if(m_CsvUtil == NULL)
	{
		m_CsvUtil = new CsvUtil();
		if(m_CsvUtil && m_CsvUtil->init())
		{
			m_CsvUtil->autorelease();
			m_CsvUtil->retain();
		}
		else
		{
			CC_SAFE_DELETE(m_CsvUtil);
			m_CsvUtil = NULL;
		}
	}
	return m_CsvUtil;
}
bool CsvUtil::init()
{
	return true;
}
void CsvUtil::loadFile(const char*sPath)
{
	CsvData*csvData = CsvData::create();
	std::string str = FileUtils::getInstance()->getStringFromFile(sPath);

	ValueVector linesList = StringUtil::getInstance()->split(str.c_str(),"\n");

	for(auto value : linesList)
	{
		ValueVector tArr = StringUtil::getInstance()->split(value.asString().c_str(),",");
		csvData->addLineData(tArr);
	}
	mCsvMap.insert(sPath,csvData);
}
const Size CsvUtil::getFileRowColNum(const char*csvFilePath)
{
	auto csvData = mCsvMap.at(csvFilePath);

	if(csvData == nullptr)
	{
		loadFile(csvFilePath);
		csvData = mCsvMap.at(csvFilePath);
	}
	Size size = csvData->getRowColNum();
	return size;
}
Value CsvUtil::getValue(int iRow,int iCol,const char*csvFilePath)
{
	auto csvData = mCsvMap.at(csvFilePath);

	if(csvData == nullptr)
	{
		loadFile(csvFilePath);
		csvData = mCsvMap.at(csvFilePath);
	}
	ValueVector rowVector = csvData->getSingleLineData(iRow);
	Value colValue = rowVector.at(iCol);
	return colValue;
}
const std::string CsvUtil::get(int iRow,int iCol,const char*csvFilePath)
{
	Value colValue = getValue(iRow,iCol,csvFilePath);

	return colValue.asString();
}
const int CsvUtil::getInt(int iRow,int iCol,const char*csvFilePath)
{
	Value colValue = getValue(iRow,iCol,csvFilePath);
	return colValue.asInt();
}
//const float CsvUtil::getFloat