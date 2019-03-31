#ifndef __HelpfulFish_H__
#define __HelpfulFish_H__
#include "Fish.h"

class HelpfulFish:public Entity
{
	CC_SYNTHESIZE(bool,m_bCaught,Caught);//是否活着
private:
	Sprite*m_pRealSprite;//真实的鱼
public:
	HelpfulFish();
	~HelpfulFish();
	static HelpfulFish*create(Fish*pFish);
	bool init(Fish*pFish);
	 
	void runNormalAnimation(Fish*pFish);
	float runDeadAnimation(Fish*pFish);
	//更新精灵状态
	void updateSpriteStatus(Fish*pFish);
};
#endif