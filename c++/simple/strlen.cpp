/**
strlen��ʵ��
1.ͨ���ݹ�
2.ͨ����\0������Ҫ����

*/
#include "iostream"
#include "assert.h"
using namespace std;

int myStrlen1(const char*str);
int myStrlen2(const char*str);

int main()
{
    const char*str = "I love you";

    cout<<"myStrlen1(str) "<<myStrlen1(str)<<endl;
    cout<<"myStrlen2(str) "<<myStrlen2(str)<<endl;

    return 0;
}
///��Ҫ����
int myStrlen1(const char*str)
{
    int len = 0;
    for(int i = 0;str[i] != '\0';i++)
    len++;

    return len;
}
///�ݹ�ʵ��
int myStrlen2(const char*str)
{
    assert(str != NULL);

    static int n = 0;
    if(*str != '\0')
    {
        cout<<n++<<endl;
        return (myStrlen2(str + 1) + 1);
    }
    else
    return 0;
}
