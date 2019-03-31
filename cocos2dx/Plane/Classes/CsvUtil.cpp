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
void CsvUtil::destroyInstance()
{
	CC_SAFE_DELETE(m_pInstance);
}
void CsvUtil::purge()
{
	for(auto iter = m_allCsvData.begin();iter != m_allCsvData.end();++iter)
		iter->second->release();
}
CsvData* CsvUtil::loadFile(const char*fileName)
{
	if(m_allCsvData.find(fileName) != m_allCsvData.end())
		return m_allCsvData.find(fileName)->second;

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
	//保存引用
	csvData->retain();
	//整理数据
	for(int i=0;i<lines.size();i++)
	{
		ValueVector line = StringUtil::split(lines.at(i).asString(),",");
		csvData->addLineData(line);
	}
	m_allCsvData.insert(std::make_pair(fileName,csvData));

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
}/*nRow nCol都是从0开始*/
Value CsvUtil::getValue(int nRow,int nCol,const std::string &fileName)
{
	auto csvData = m_allCsvData.at(fileName);
	Value value;
	if(!csvData)
	{
		csvData = loadFile(fileName.c_str());
	}
	ValueVector line = csvData->getSingleLineData(nRow);
	value = line.at(nCol);
	return value;
}
int CsvUtil::findLineByValue(Value value,int column,std::string fileName)
{
	CsvData*csvData = nullptr;
	if(m_allCsvData.find(fileName) == m_allCsvData.end())
		csvData = loadFile(fileName.c_str());
	else
		csvData = m_allCsvData.find(fileName)->second;
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