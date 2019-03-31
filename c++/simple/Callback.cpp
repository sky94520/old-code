#include<string>
#include<iostream>
using namespace std;
class People
{
    public:
    void name(std::string str)
    {
        cout<<str<<endl;
    }
};
typedef void (People::*SEL_CallFunc)(string str);
#define callFunc_selector(_SELECTOR) (SEL_CallFunc)(&_SELECTOR)
class Student : public People
{
private:
    string name;
    int age;
public:
    Student(string name,int age)
    {
        this->name=name;
        this->age=age;
    }
    //�ص�����
    void callback(string str)
    {
        cout<<"My name is "<< str<<endl<< "age is "<<age<<endl;
    }
    //say���������ûص�����
    void say()
    {
        cout<<"this is a student!"<<endl;
        m_pSelector=callFunc_selector(Student::callback);//(SEL_CallFunc)(&Student::callback);
        m_pListen=this;
        (m_pListen->*m_pSelector)(name);
    }
protected:
    //�ص���ִ����
    People*m_pListen;
    //�ص�����ָ��
    SEL_CallFunc m_pSelector;
};
int main()
{
    Student*a=new Student("Сţ",22);
    a->say();
    return 0;
}
