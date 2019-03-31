#ifndef __Game_H__
#define __Game_H__
#include<vector>
#include<Windows.h>

using namespace std;

class BackgroundLayer;

class Game
{
private:
	BackgroundLayer*m_pBackgroundLayer;
public:
	Game();
	~Game();
	BOOL gameInit(HWND hWnd);
	void gamePaint(HWND hWnd);
	void gameUpdate(HWND hWnd);
	BOOL gameCleanup(HWND hWnd);
	//监听鼠标移动事件和鼠标左键按下事件
	void gameMouseMotion(WORD x,WORD y);
	//鼠标左键按下信息
	void gameMouseBtn(WORD x,WORD y);
};

#endif
