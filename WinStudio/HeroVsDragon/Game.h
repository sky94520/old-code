#ifndef __Game_H__
#define __Game_H__
#include<vector>
#include<Windows.h>

enum ActionTypes
{
	ACTION_TYPE_NORMAL=0,//��ͨ����
	ACTION_TYPE_CRITICAL=1,//����һ��
	ACTION_TYPE_MAGIC=2,//ħ������
	ACTION_TYPE_MISS=3,//�������
	ACTION_TYPE_RECOVER=4//�ָ�ħ��
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
	vector<Button*> m_skillBtns;//���Ǽ��ܰ���
	Skill*m_pNormalSkill;//��ͨ����
public:
	Game();
	~Game();
	BOOL gameInit(HWND hWnd);
	void gamePaint(HWND hWnd);
	BOOL gameCleanup(HWND hWnd);
	//��������ƶ��¼��������������¼�
	void gameMouseMotion(WORD x,WORD y);
	//������������Ϣ
	void gameMouseBtn(WORD x,WORD y);
};

#endif
