#include<iostream>
using namespace std;
//��ģ��
template<typename T>
class Unique_ptr
{
	private:
		T*point;
	public:
		Unique_ptr(T*p):point(p){}
		T max()
		{return (x > y)?x:y;}
		T min()
		{return (x < y)?x:y;}
		friend ostream&operator<<(ostream &out,const Unique_ptr&c);
};
ostream &operator<<(ostream &out,const Unique_ptr &c)
{
	out<<
}
//�����࣬������ > <
class Intger
{
	private:
		int real;
	public:
		Intger(int r):real(r){}
		//>
		bool operator>(const Intger &c2)
		{
			return real>c2.real?true:false;
		}
		bool operator<(const Intger &c2)
		{
			return real<c2.real?true:false;
		}
};
int main()
{
	return 0;
}
