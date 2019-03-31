#ifndef __Game_H__
#define __Game_H__
#include<vector>
#include<Windows.h>

enum ActionTypes
{
	ACTION_TYPE_NORMAL=0,//普通攻击
	ACTION_TYPE_CRITICAL=1,//致命一击
	ACTION_TYPE_MAGIC=2,//魔法攻击
	ACTION_TYPE_MISS=3,//攻击落空
	ACTION_TYPE_RECOVER=4//恢复魔法
};

class Player;
class Monster;
class Button;
class Skill;

using namespace std;

class Game
{
private:
	Player*m_pPlayer;
	Monster*m_pBoss;
	vector<Button*> m_skillBtns;//主角技能按键
	Skill*m_pNormalSkill;//普通攻击
public:
	Game();
	~Game();
	BOOL gameInit(HWND hWnd);
	void gamePaint(HWND hWnd);
	BOOL gameCleanup(HWND hWnd);
	//监听鼠标移动事件和鼠标左键按下事件
	void gameMouseMotion(WORD x,WORD y);
	//鼠标左键按下信息
	void gameMouseBtn(WORD x,WORD y);
};

#endif
