#include<iostream>
#include<string>
#include<conio.h>
#include "lua/lua.h"
#include "TextureManager.h"
#include "Point.h"
#include "Size.h"
#include "MainLua.h"
#include "GameScene.h"
#include "Player.h"
#include "Monster.h"
#include "GlobalFunctions.h"
using namespace std;

int key = 0;
Player*m_pPlayer = nullptr;
GameScene*m_pGameScene = nullptr;
bool g_bRunning = true;

int LUA_playerUp(lua_State*pL);
int LUA_playerDown(lua_State*pL);
int LUA_playerLeft(lua_State*pL);
int LUA_playerRight(lua_State*pL);
int LUA_gameOver(lua_State*pL);//游戏结束
int LUA_showPackageLayer(lua_State*pL);//展示背包界面
int LUA_Hurt(lua_State*pL);//受伤时调用
int LUA_Text(lua_State*pL);//输出文本
int LUA_HandleInteractiveEvent(lua_State*pL);//处理交互事件
int main()
{
	//lua
	lua_State*pL =  MainLua::getInstance()->getLuaState();
	//加载脚本文件 并执行
	luaL_dofile(pL,"script/test.lua");
	luaL_dofile(pL,"script/weapon.lua");
	luaL_dofile(pL,"script/monster.lua");
	//把c函数寄存到lua中
	lua_register(pL,"LUA_playerUp",LUA_playerUp);
	lua_register(pL,"LUA_playerDown",LUA_playerDown);
	lua_register(pL,"LUA_playerLeft",LUA_playerLeft);
	lua_register(pL,"LUA_playerRight",LUA_playerRight);
	lua_register(pL,"LUA_gameOver",LUA_gameOver);
	lua_register(pL,"LUA_showPackageLayer",LUA_showPackageLayer);
	lua_register(pL,"LUA_Hurt",LUA_Hurt);
	lua_register(pL,"LUA_Text",LUA_Text);
	lua_register(pL,"LUA_HandleInteractiveEvent",LUA_HandleInteractiveEvent);
	m_pGameScene = new GameScene();
	m_pGameScene->init();
	m_pPlayer = m_pGameScene->getPlayer();
	while(g_bRunning)
	{
		system("cls");

		m_pGameScene->render();
		TextureManager::getInstance()->render();
		key = GlobalFunctions::getcha();//接收按键
		//发送按键给lua
		lua_getglobal(pL,"handleKey");
		lua_pushnumber(pL,key);
		lua_call(pL,1,0);
	}
	delete m_pGameScene;
	MainLua::getInstance()->purge();
	TextureManager::getInstance()->purge();
	return 0;
}
//把输入传递给脚本
//传递给lua的函数必须是下面这种形式
//返回值代表，有几个返回参数
int LUA_playerUp(lua_State*pL)
{
	Point pos = m_pPlayer->getPosition();
	Point pos2 = Point(pos.x,pos.y-1);
	Size visibleSize = TextureManager::getInstance()->getVisibleSize();
	if(visibleSize.containsPoint(pos2))
	{
		m_pPlayer->setPosition(pos2);
		m_pGameScene->setColliabledEntity(nullptr);
	}
	return 0;
}
int LUA_playerDown(lua_State*pL)
{
	Point pos = m_pPlayer->getPosition();
	Point pos2 = Point(pos.x,pos.y + 1);
	Size visibleSize = TextureManager::getInstance()->getVisibleSize();
	if(visibleSize.containsPoint(pos2))
	{
		m_pPlayer->setPosition(pos2);
		m_pGameScene->setColliabledEntity(nullptr);
	}
	return 0;
}
int LUA_playerLeft(lua_State*pL)
{
	Point pos = m_pPlayer->getPosition();
	Point pos2 = Point(pos.x - 1,pos.y);
	Size visibleSize = TextureManager::getInstance()->getVisibleSize();
	if(visibleSize.containsPoint(pos2))
	{
		m_pPlayer->setPosition(pos2);
		m_pGameScene->setColliabledEntity(nullptr);
	}
	return 0;
}
int LUA_playerRight(lua_State*pL)
{
	Point pos = m_pPlayer->getPosition();
	Point pos2 = Point(pos.x + 1,pos.y);
	Size visibleSize = TextureManager::getInstance()->getVisibleSize();
	if(visibleSize.containsPoint(pos2))
	{
		m_pPlayer->setPosition(pos2);
		m_pGameScene->setColliabledEntity(nullptr);
	}
	return 0;
}
int LUA_gameOver(lua_State*pL)
{
	g_bRunning = false;
	return 0;
}
int LUA_showPackageLayer(lua_State*pL)
{
	m_pGameScene->showPackage();
	return 0;
}
int LUA_Hurt(lua_State*pL)
{
	std::string monsterID = luaL_checkstring(pL,1);
	int damage = luaL_checknumber(pL,2);
	//主人公受伤
	if(monsterID == "player")
	{
		m_pPlayer->hurt(damage);
		return 0;
	}
	auto monsters = m_pGameScene->getMonsters();
	for(int i=0;i<monsters->size();i++)
	{
		auto monster = monsters->at(i);
		if(monster->getID() == monsterID)
		{
			monster->hurt(damage);
		}
	}
	return 0;
}
int LUA_Text(lua_State*pL)
{
	std::string text = luaL_checkstring(pL,1);
	std::cout<<text<<endl;
	return 0;
}
int LUA_HandleInteractiveEvent(lua_State*pL)
{
	auto pCollidedEntity = m_pGameScene->getColliabledEntity();
	if(pCollidedEntity)
	{
		pCollidedEntity->collided();
		m_pGameScene->setColliabledEntity(nullptr);
	}
	return 0;
}