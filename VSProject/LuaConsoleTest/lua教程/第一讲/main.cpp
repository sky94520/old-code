#include<iostream>
#include<string>
#include<conio.h>
#include "lua/lua.h"
#include "Player.h"
using namespace std;

Player*m_pPlayer = nullptr;
int LUA_playerUp(lua_State*pL);
int LUA_playerDown(lua_State*pL);
int LUA_playerLeft(lua_State*pL);
int LUA_playerRight(lua_State*pL);
int main()
{
	int key = 0;
	m_pPlayer = new Player();
	m_pPlayer->setPosition(4,4);
	m_pPlayer->bindSprite('@');
	//lua
	lua_State*pL = luaL_newstate();
	luaL_openlibs(pL);
	//加载脚本文件 并执行
	luaL_dofile(pL,"script/test.lua");
	//把c函数寄存到lua中
	lua_register(pL,"LUA_playerUp",LUA_playerUp);
	lua_register(pL,"LUA_playerDown",LUA_playerDown);
	lua_register(pL,"LUA_playerLeft",LUA_playerLeft);
	lua_register(pL,"LUA_playerRight",LUA_playerRight);

	while(true)
	{
		m_pPlayer->render();
		key = _getch();//接收按键
		//发送按键给lua
		lua_getglobal(pL,"handleKey");
		lua_pushnumber(pL,key);
		lua_call(pL,1,0);
		system("cls");
	}

	delete m_pPlayer;
	lua_close(pL);
	return 0;
}
//把输入传递给脚本
//传递给lua的函数必须是下面这种形式
//返回值代表，有几个返回参数
int LUA_playerUp(lua_State*pL)
{
	Point pos = m_pPlayer->getPosition();
	m_pPlayer->setPosition(pos.x,pos.y-1);
	return 0;
}
int LUA_playerDown(lua_State*pL)
{
	Point pos = m_pPlayer->getPosition();
	m_pPlayer->setPosition(pos.x,pos.y + 1);
	return 0;
}
int LUA_playerLeft(lua_State*pL)
{
	Point pos = m_pPlayer->getPosition();
	m_pPlayer->setPosition(pos.x - 1,pos.y);
	return 0;
}
int LUA_playerRight(lua_State*pL)
{
	Point pos = m_pPlayer->getPosition();
	m_pPlayer->setPosition(pos.x + 1,pos.y);
	return 0;
}