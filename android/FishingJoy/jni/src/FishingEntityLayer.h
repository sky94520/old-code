#ifndef __FishingEntityLayer_H__
#define __FishingEntityLayer_H__

#include<list>
#include "SDL_Engine/SDL_Engine.h"

using namespace SDL;
using namespace std;

class Fish;
class FishingNet;
class FishingEntity;

class FishingEntityLayerDelegate
{
public:
	virtual ~FishingEntityLayerDelegate(){}
	virtual void fireEnd()=0;
};

class FishingEntityLayer:public Layer
{
private:
	list<FishingEntity*> m_fishingEntitys;
	FishingEntityLayerDelegate*m_pDelegate;
public:
	FishingEntityLayer();
	~FishingEntityLayer();
	CREATE_FUNC(FishingEntityLayer);
	bool init();

	void update(float dt);

	void setDelegate(FishingEntityLayerDelegate*pDelegate);
	//ÃÌº”FishingNet
	void addFishingNet(int lv,const Point&pos,float rotation);
	//ÃÌº”º§π‚
	void addLaser(const Point&pos,float rotation);
	//ÃÌº”’‰÷ÈµØ
	void addPearl(const Point&pos,float rotation);
	//ÃÌº”√‘ŒÌ
	void addFog(Fish*fish,const Point&pos,float rotation);
};
#endif