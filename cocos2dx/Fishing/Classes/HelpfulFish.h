#ifndef __HelpfulFish_H__
#define __HelpfulFish_H__
#include "Fish.h"

class HelpfulFish:public Entity
{
	CC_SYNTHESIZE(bool,m_bCaught,Caught);//�Ƿ����
private:
	Sprite*m_pRealSprite;//��ʵ����
public:
	HelpfulFish();
	~HelpfulFish();
	static HelpfulFish*create(Fish*pFish);
	bool init(Fish*pFish);
	 
	void runNormalAnimation(Fish*pFish);
	float runDeadAnimation(Fish*pFish);
	//���¾���״̬
	void updateSpriteStatus(Fish*pFish);
};
#endif