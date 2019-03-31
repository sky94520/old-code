#include<iostream>
#include<string>
#include <conio.h>
#include "lua.h"
using namespace std;

int main(int argc,char**argv)
{
	lua_State*pL = luaL_newstate();
	luaL_openlibs(pL);
	//ִ�нű�
	int ret = luaL_dofile(pL,"ScriptEvent.lua");

	if (ret != 0)
	{
		printf("error:%s",luaL_checkstring(pL,-1));
	}
	//��ȡtable��Ӧ�ĺ���
	lua_getglobal(pL,"npc01");
	lua_pushliteral(pL,"initlize");
	lua_gettable(pL,-2);
	//�������
	lua_getglobal(pL,"npc01");
	lua_pushinteger(pL,10);
	//ִ��
	ret = lua_pcall(pL,2,0,0);

	getchar();
	lua_close(pL);
	return 0;
}
/*int main(int argc,char**argv)
{
	//�½�lua
	lua_State*pL = luaL_newstate();
	//�򿪻�����
	luaL_openlibs(pL);
	//Ҫִ�еĴ����
	string script;
	cout<<"Lua 5.2 Copyright (C) LUAConsole"<<endl;
	cout<<"os.exit() or QUIT to exit"<<endl;
	cout<<"------------------------------------------------------------------------"<<endl;
	do
	{
		cout<<"Ready>";
		//��ȡ����
		getline(cin,script);
		
		if(luaL_loadbuffer(pL,script.c_str(),script.size(),0) != LUA_OK
			|| lua_pcall(pL,0,0,0) != LUA_OK)
		{
			cout<<luaL_checkstring(pL,-1)<<endl;
		}
	}
	while(script != "QUIT");
	lua_close(pL);
	return 0;
}*/