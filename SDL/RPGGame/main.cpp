#include<iostream>
#include "stdio.h"
#include "cstdlib"
#include "conio.h"
//
#ifdef __linux
#define __APK
#else
#include <windows.h>
#endif

using namespace std;

void delay(float time);
void cls();
void gotoXY(int x, int y);
void HideCursor();

#include "Classes/Point.cpp"
#include "Classes/Entity.cpp"
#include "Classes/Player.cpp"
#include "Classes/HandleKey.cpp"
#include "Classes/Scene.cpp"
#include "Classes/VillageScene.cpp"
//
HandleKey *handleKey;
// int key = 0;
// ����
int main()
{
    ///隐藏光标
    ///HideCursor();
  // 处理按键
  handleKey = new HandleKey();
  // 人物
  Player *player = new Player();
  player->setPosition(Point(40, 20));
  player->bindSprite('$');
  // 场景类
  VillageScene *villageScene = VillageScene::create();
  Scene::bindPlayer(player);
  while (1)
  {
    while (villageScene->isAlive())
    {
    	//画出人物，背景 怪物
    	villageScene->draw();
    	//接收按键
      handleKey->getKey();
      //处理按键
      switch (handleKey->judgeKey())
      {
      case UP:
      //gotoXY(player->getPositionX(),player->getPositionY());
      //cout<<" ";
        player->setPositionY(player->getPositionY() - 1);

        break;
      case DOWN:
        player->setPositionY(player->getPositionY() + 1);
        break;
      case LEFT:
        player->setPositionX(player->getPositionX() - 1);
        break;
      case RIGHT:
        player->setPositionX(player->getPositionX() + 1);
        break;
        case PLAYER_PROPERTY:
        cout<<*player;
        //player->show();
        cout<<"按任意键继续..."<<endl;
        _getch();
        break;
      }
      //判断碰撞等
      villageScene->update();
      delay(100);
      cls();
    }//villageScene while
  }
  return 0;
}

void cls()
{

#ifdef __APK
  clrscr();
#else
  system("cls");
#endif // __APK

}
void delay(float time)
{
#ifdef __APK
  usleep(time);
#else
  Sleep(time);
#endif // __APK
}
void gotoXY(int x, int y)
{
#ifdef __APK
  gotoxy(x, y);
#else
  HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD pos;
  pos.X = x;
  pos.Y = y;
  SetConsoleCursorPosition(hOut, pos);
#endif
}
///隐藏光标
void HideCursor()
{
    #ifndef __APK
    CONSOLE_CURSOR_INFO cursor_info = {1, 0};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
    #endif
}

