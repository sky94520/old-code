#ifndef __ScoreSprite_H__
#define __ScoreSprite_H__
#include<string>
#include "SDL_Engine/SDL_Engine.h"
using namespace std;
using namespace SDL;

class ScoreSprite:public Node
{
private:
	Sprite*m_pPrizeSign;//乘号精灵
	LabelAtlas*m_pPrizeNum;//数字精灵
public:
	ScoreSprite();
	~ScoreSprite();

	static ScoreSprite*create(int score);

	bool init(int score);
	/**内部调用淡出动画，并返回完全淡出的时间*/
	float runFadeOutAction();
	/**设置数字*/
	void setScore(int score);
};
#endif