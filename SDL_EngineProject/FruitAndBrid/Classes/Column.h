#ifndef __Column_H__
#define __Column_H__
#include "Entity.h"
typedef enum ColumnType
{
	kColumn_Top,
	kColumn_Bottom
}ColumnType;
class Column:public Entity
{
private:
	ColumnType m_type;//����
	unsigned int m_nLen;//����
public:
	Column();
	~Column();
	static Column*create(unsigned int len,ColumnType type);
	bool init(unsigned int len,ColumnType type);

	void setLen(unsigned int len);
};
#endif