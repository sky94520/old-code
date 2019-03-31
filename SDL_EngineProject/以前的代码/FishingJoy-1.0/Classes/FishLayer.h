#ifndef __FishLayer_H__
#define __FishLayer_H__
#include "SDL_Engine/SDL_Engine.h"
#include "Fish.h"
using namespace SDL;
#define MAX_FISH_NUM 20//最大鱼的数量
class FishLayer:public Layer
{
private:
	int m_nNotVisibleFishNum;
	bool m_bReset;
	std::vector<Fish*> m_fishes;
public:
	FishLayer();
	~FishLayer();
	CREATE_FUNC(FishLayer);
	bool init();
public:
	virtual void update(float dt);
	std::vector<Fish*> getFishes()const;
};
#endif