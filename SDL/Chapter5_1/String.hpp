#include <cstring>
#include <cstdio>

#pragma once

class String
{
  private:
	char *point;
  public:
	  String();
	  String(const char *str);
	  String(double str);
	 ~String();
	// 返回c语言字符串
	char *c_str() const;
	// 返回字符串大小
	int size();
	// 复制构造函数
	  String(const String & str);
	// 操作符重载
	  String & operator=(const String & s);
	  String & operator+=(const String & s);
	char &operator[] (int sub);

	// friend
	friend std::ostream & operator<<(std::ostream & out, const String & s);
	friend std::istream & operator>>(std::istream & in, String & s);
	String operator+(const String & s);
};
String::String()
{
	point = NULL;
}

String::String(const char *str)
{
	point = new char[strlen(str) + 1];
	strcpy(point, str);
	// cout << point << "调用了构造函数" << endl;
}

String::String(double str)
{
	char ch[100];
	if (str == (int)str)
		sprintf(ch, "%.0lf", str);
	else if (str > (int)str)
		sprintf(ch, "%.4lf", str);
	point = new char[strlen(ch) + 1];
	strcpy(point, ch);
}

String::~String()
{
	 //std::cout << point << ":调用了析构函数" << std::endl;
	if (point == NULL)
		return;

	delete[]point;
	point = NULL;
}

char *String::c_str()
	 const
	 {
		 return point;
	 }
	 int String::size()
{
	if (point == NULL)
		return 0;
	return strlen(point);
}

char &String::operator[] (int sub)
{
	// 暂时不做处理
	/* 经个人测试得， string对于数组越界并未
	   做什么错误处理 */
	do
	{
		if (sub >= strlen(point))
			throw sub;
		return point[sub];
	}
	while (0);
}

String::String(const String & s)
{
	point = new char[strlen(s.point) + 1];
	strcpy(point, s.point);
	// cout << point << "调用了复制构造函数" << endl;
}

String & String::operator=(const String & s)
{
	/* 为什么不能用if(*this == s) 答 s为const String
	   所以值不能变 */
	// 避免自己给自己赋值
	if (this == &s)
		return *this;
	delete[]point;
	point = new char[strlen(s.point) + 1];
	strcpy(point, s.point);

	return *this;
}

String & String::operator+=(const String & s)
{
	char *p = new char[strlen(point) + strlen(s.point) + 1];
	strcpy(p, point);
	strcat(p, s.point);

	delete[]point;
	point = p;
	return *this;
}

std::ostream & operator<<(std::ostream & out, const String & s)
{
	out << s.point;

	return out;
}

std::istream & operator>>(std::istream & in, String & s)
{
	char *p = new char[256];
	in.getline(p, 256, '\n');

	delete[]s.point;
	s.point = new char[strlen(p) + 1];
	strcpy(s.point, p);
	delete[]p;
	return in;
}

String String::operator+(const String & s)
{
	char *p = new char[strlen(point) + strlen(s.point) + 1];
	strcpy(p, point);
	strcat(p, s.point);

	String str(p);

	return str;
}