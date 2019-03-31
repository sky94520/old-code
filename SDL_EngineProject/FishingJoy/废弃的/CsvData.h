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
	//������д�С
	Size getRowColNum();
	//������
	void addLineData(ValueVector lineVector);
	//���������
	ValueVector getSingleLineData(int row);
};
#endif