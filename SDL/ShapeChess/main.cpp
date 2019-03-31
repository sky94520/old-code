#include<iostream>
#include<vector>
#include<cstdlib>
using namespace std;

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

#include "Classes/Director.h"
#include "Classes/Font.h"

#include "Chess.hpp"

int main(int argc, char **argv)
{
	//用于输出输赢情况
	char ch[100];
	// 接收事件
	SDL_Event event;

	Director::init();
	// 初始化棋盘
	Chess *chess = new Chess();
	chess->bindRenderer(Director::getInstance()->getRenderer());
	chess->setDPI(Director::getInstance()->getVisibleSize().w,
				  Director::getInstance()->getVisibleSize().h);

	Font *text = new Font(100);
	text->bindRenderer(Director::getInstance()->getRenderer());
	// 设置划线颜色
	SDL_SetRenderDrawColor(Director::getInstance()->getRenderer(), 255, 0, 0, 0);

	while (chess->isEnd() == false)
	{
		while (!SDL_PollEvent(&event))
		{
			// 画出棋盘与棋子
			chess->draw();
			text->printText(ch,{10,200},{125,32,199});
			SDL_RenderPresent(Director::getInstance()->getRenderer());
		}
		chess->handleEvent(event);
	}
	
	sprintf(ch,"%s",chess->isEnd() == CHESS_OX?"平局":(chess->isEnd() == CHESS_O ? "O赢了":"X赢了"));
	chess->draw();
	
	text->printText(ch,{0, 800},{125, 32, 199});
	SDL_RenderPresent(Director::getInstance()->getRenderer());
	SDL_Delay(1000);
	
	delete chess;
	delete text;
	return 0;
}

// text->printText("X",{10,200},{125,32,199});