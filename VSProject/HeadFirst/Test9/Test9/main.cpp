#include<iostream>
#include<string>
#include<conio.h>
#include "Menu.h"
#include "MenuItem.h"

using namespace std;

int main()
{
	MenuComponent*pancakeHouseMenu = new Menu("Сţ���","��Ӫ�緹");
	//����˵���
	pancakeHouseMenu->add(new MenuItem("��ͷ","�óԵ���ͷ",true,3.89));
	pancakeHouseMenu->add(new MenuItem("����","�ճ�¯���Ȱ���",true,3.89));
	//�����Ӳ˵�
	MenuComponent*breakfast = new Menu("�������","���ʱ���");
	breakfast->add(new MenuItem("��ĥ����","��֤",true,1.5));
	breakfast->add(new MenuItem("�̲�","��ݵ�����",true,2.5));

	pancakeHouseMenu->add(breakfast);
	pancakeHouseMenu->print();

	_getch();
	return 0;
}