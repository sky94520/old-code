#include "CsvUtil.h"
#include "CsvData.h"
#include "StringUtil.h"
CsvUtil*CsvUtil::m_pInstance = NULL;
CsvUtil::CsvUtil()
{
}
CsvUtil::~CsvUtil()
{
}
CsvUtil*CsvUtil::getInstance()
{
	if(m_pInstance == NULL)
		m_pInstance = new CsvUtil();
	return m_pInstance;
}
CsvData* CsvUtil::loadFile(const char*fileName)
{
	if(m_allCsvData.at(fileName))
		return m_allCsvData.at(fileName);

	std::ifstream csvStream(fileName,std::ios::in | std::ios::_Nocreate);
	ValueVector lines;
	while(!csvStream.eof())
	{
		std::string line;
		csvStream>>line;
		lines.push_back(Value(line));
	}
	csvStream.close();
	//根据文件名保存
	//std::string data = FileUtils::getInstance()->getStringFromFile(fileName);
	CsvData*csvData = CsvData::create();
	//整理数据
	for(int i=0;i<lines.size();i++)
	{
		ValueVector line = StringUtil::getInstance()->split(lines.at(i).asString(),",");
		csvData->addLineData(line);
	}
	m_allCsvData.insert(fileName,csvData);

	return csvData;
}
Size CsvUtil::getRowColNum(std::string name)
{
	Size size = Size::ZERO;
	auto csvData = m_allCsvData.at(name);
	//如果不存在，则加载
	if(csvData == NULL)
	{
		size = loadFile(name.c_str())->getRowColNum();
	}
	else
		size = csvData->getRowColNum();
	return size;
}
Value CsvUtil::getValue(int nRow,int nCol,const char*fileName)
{
	auto csvData = m_allCsvData.at(fileName);
	Value value;
	if(!csvData)
	{
		csvData = loadFile(fileName);
	}
	ValueVector line = csvData->getSingleLineData(nRow);
	value = line.at(nCol);
	return value;
}
int CsvUtil::findLineByValue(Value value,int column,std::string fileName)
{
	auto csvData = m_allCsvData.at(fileName);
	if(csvData == NULL)
		csvData = loadFile(fileName.c_str());
	//获得行列大小
	Size size = csvData->getRowColNum();
	if(column < size.height)
	{
		//搜索数据所在的行
		for(int i=0;i<size.width;i++)
		{
			ValueVector temp = csvData->getSingleLineData(i);
			if(temp.at(column).asString() == value.asString())
				return i;
		}
	}
	return -1;
}