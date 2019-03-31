#ifndef __ScoreSprite_H__
#define __ScoreSprite_H__
#include<string>
#include "SDL_Engine/SDL_Engine.h"
using namespace std;
using namespace SDL;

class ScoreSprite:public Node
{
private:
	Sprite*m_pPrizeSign;//�˺ž���
	LabelAtlas*m_pPrizeNum;//���־���
public:
	ScoreSprite();
	~ScoreSprite();

	static ScoreSprite*create(int score);

	bool init(int score);
	/**�ڲ����õ�����������������ȫ������ʱ��*/
	float runFadeOutAction();
	/**��������*/
	void setScore(int score);
};
#endif