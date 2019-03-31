#include<iostream>
#include<string>
#include<conio.h>
#include "Menu.h"
#include "MenuItem.h"

using namespace std;

int main()
{
	MenuComponent*pancakeHouseMenu = new Menu("小牛店家","主营早饭");
	//加入菜单项
	pancakeHouseMenu->add(new MenuItem("馒头","好吃的馒头",true,3.89));
	pancakeHouseMenu->add(new MenuItem("包子","刚出炉的热包子",true,3.89));
	//增加子菜单
	MenuComponent*breakfast = new Menu("早餐饮料","保质保量");
	breakfast->add(new MenuItem("现磨豆浆","保证",true,1.5));
	breakfast->add(new MenuItem("奶茶","身份的象征",true,2.5));

	pancakeHouseMenu->add(breakfast);
	pancakeHouseMenu->print();

	_getch();
	return 0;
}