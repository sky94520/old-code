#include "CsvData.h"
CsvData::CsvData()
{
}
CsvData::~CsvData()
{
	m_allData.clear();
}
bool CsvData::init()
{
	return true;
}
void CsvData::addLineData(ValueVector lineVector)
{
	m_allData.push_back(Value(lineVector));
}
ValueVector CsvData::getSingleLineData(int row)
{
	ValueVector value;
	if(row < m_allData.size())
		value = m_allData.at(row).asValueVector();
	return value;
}
Size CsvData::getRowColNum()
{
	Size size = Size::ZERO;
	size.width = m_allData.size();
	if(size.width > 0)
	{
		ValueVector value = getSingleLineData(0);
		size.height = value.size();
	}
	return size;
}