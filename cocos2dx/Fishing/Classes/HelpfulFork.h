#ifndef __HelpfulFork_H__
#define __HelpfulFork_H__
#include "Entity.h"
class HelpfulFork:public Entity
{
private:
	Sprite*m_pRealSprite;
public:
	HelpfulFork();
	~HelpfulFork();
	CREATE_FUNC(HelpfulFork);
	bool init();

	float runMovingAction(const Point&endPos1,const Point&endPos2);
};
#endif