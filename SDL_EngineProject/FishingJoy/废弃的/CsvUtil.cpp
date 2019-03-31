#include "CsvUtil.h"
#include "CsvData.h"
CsvUtil*CsvUtil::m_pInstance = NULL;
CsvUtil::CsvUtil()
{
}
CsvUtil::~CsvUtil()
{
	for(auto iter = m_allCsvData.begin();iter != m_allCsvData.end();)
	{
		auto data = iter->second;
		iter = m_allCsvData.erase(iter);
		data->release();
	}
}
CsvUtil*CsvUtil::getInstance()
{
	if(m_pInstance == NULL)
		m_pInstance = new CsvUtil();
	return m_pInstance;
}
void CsvUtil::purge()
{
	SDL_SAFE_DELETE(m_pInstance);
}
CsvData* CsvUtil::loadFile(const char*fileName)
{
	auto iter = m_allCsvData.find(fileName);

	if(iter != m_allCsvData.end())
		return iter->second;
	auto text = FileUtils::getInstance()->getDataFromFile(fileName);
	if(text.empty())
		return nullptr;

	stringstream csvStr(text);
	
	ValueVector lines;
	while(!csvStr.eof())
	{
		std::string line;
		csvStr>>line;
		Value value = Value(line);
		//value = line;
		lines.push_back(value);
	}
	//根据文件名保存
	CsvData*csvData = CsvData::create();
	//保存引用
	csvData->retain();
	//整理数据
	for(unsigned int i=0;i<lines.size();i++)
	{
		ValueVector line = StringUtils::split(lines.at(i).asString(),",");
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
	int line = -1;

	if(m_allCsvData.find(fileName) == m_allCsvData.end())
		csvData = loadFile(fileName.c_str());
	else
		csvData = m_allCsvData.find(fileName)->second;
	//获得行列大小
	Size size = csvData->getRowColNum();

	auto startTick = SDL_GetTicks();

	if(column < size.height)
	{
		//搜索数据所在的行
		for(int i=0;i<size.width;i++)
		{
			const ValueVector& temp = csvData->getSingleLineData(i);

			/*if(temp.at(column).asString() == value.asString())
			{
				line = i;
				break;
			}*/
			auto iter = find_if(temp.begin(),temp.end(),[value](Value t)
			{
				return t.asString() == value.asString();
			});

			printf(" %d ",SDL_GetTicks() - startTick);

			if(iter != temp.end())
			{
				line = i;
				break;
			}
		}
	}

	printf("inner %d \n",SDL_GetTicks() - startTick);

	return line;
}

CsvData*CsvUtil::getCsvDataForName(const std::string&filename)
{
	auto iter = m_allCsvData.find(filename);

	if(iter == m_allCsvData.end())
		return nullptr;

	auto csvData = iter->second;

	return csvData;
}