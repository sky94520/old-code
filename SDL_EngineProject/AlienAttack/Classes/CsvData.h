#ifndef __CsvData_H__
#define __CsvData_H__
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;
class CsvData : public Object
{
private:
	ValueVector m_allData;
public:
	CsvData();
	~CsvData();
	CREATE_FUNC(CsvData);
	virtual bool init();
	//获得行列大小
	Size getRowColNum();
	//增加行
	void addLineData(ValueVector lineVector);
	//获得行数据
	ValueVector getSingleLineData(int row);
};
#endif