#include<iostream>
#include<fstream>
#include<string>
#include<Windows.h>
#include "sqlite3/sqlite3.h"
#include<conio.h>

int callback(void*,int,char**,char**);

using namespace std;

int main(int argc,char**argv)
{
	sqlite3*db = nullptr;
	char*errorMsg = nullptr;
	//打开数据库
	sqlite3_open("fishing.db",&db);
	//创建表
	/*const char*sql = "create table question("\
		"id integer primary key autoincrement,"\
		"message text,"\
		"answer1 text,"\
		"answer2 text,"\
		"answer3 text,"\
		"answer4 text,"\
		"realAnswer integer);";*/
	ifstream file;
	std::string sql;

	file.open("insert.txt",ios::in);
	getline(file,sql);
	//执行命令 
	sqlite3_exec(db,sql.c_str(),callback,0,&errorMsg);
	sqlite3_close(db);

	if(errorMsg)
		cout<<errorMsg<<endl;
	else
		cout<<"添加数据成功"<<endl;

	_getch();

	return 0;
}
int callback(void*,int,char**,char**)
{
	return 0;
}