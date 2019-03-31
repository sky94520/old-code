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
	//��������ƶ��¼��������������¼�
	void gameMouseMotion(WORD x,WORD y);
	//������������Ϣ
	void gameMouseBtn(WORD x,WORD y);
};

#endif
