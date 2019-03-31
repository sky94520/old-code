#ifndef __Value_H__
#define __Value_H__
#include<string>
#include<vector>
#include<sstream>
#include <assert.h>
#include "PlatformMarcos.h"
class Value;
typedef std::vector<Value> ValueVector;
class Value
{
public:
	static const Value Null;
public:
	enum class Type
    {
        NONE = 0,
        BYTE,
        INTEGER,
        FLOAT,
        DOUBLE,
        BOOLEAN,
        STRING,
        VECTOR,
        /*MAP,
        INT_KEY_MAP*/
    };
private:
	Type _type;
	union 
	{
		unsigned char byteVal;
		int intVal;
		float floatVal;
		double doubleVal;
		bool boolVal;
		std::string*stringVal;
		ValueVector*vectorVal;
	}_field;
public:
	Value();
	explicit Value(unsigned char v);
	explicit Value(int v);
	explicit Value(float v);
	explicit Value(double v);
	explicit Value(bool v);
	explicit Value(const char*v);
	explicit Value(const std::string&v);
	explicit Value(const ValueVector&v);
	//���ƹ��캯��
	Value(const Value&v);
	~Value();
	//����=�����
	Value& operator=(const Value&v);

	Value& operator=(unsigned char v);
	Value& operator=(int v);
	Value& operator=(float v);
	Value& operator=(double v);
	Value& operator=(bool v);
	Value& operator=(const char*v);
	Value& operator=(const std::string& v);
	Value& operator=(const ValueVector& v);
	// == !=
	bool operator==(const Value&v)const;
	bool operator!=(const Value&v);
	//
	unsigned char asByte()const;
	int asInt()const;
	float asFloat()const;
	double asDouble()const;
	bool asBool()const;
	std::string asString()const;
	ValueVector asValueVector()const;
	//�Ƿ�Ϊ��
	bool isNull()const{return _type == Type::NONE;}
	Type getType()const{return _type;}
private:
	void clear();
	void reset(Type type);
};
#endif