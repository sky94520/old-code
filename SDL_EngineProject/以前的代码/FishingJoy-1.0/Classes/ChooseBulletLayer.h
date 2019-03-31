#ifndef __ChooseBulletLayer_H__
#define __ChooseBulletLayer_H__
#include "SDL_Engine/SDL_Engine.h"
#include "sundry.h"
using namespace SDL;
class BulletCard;
class ChooseBulletChildLayer;
class ChooseBulletDelegate
{
public:
	virtual void setBulletType(BulletType type)=0;
};
class ChooseBulletLayer:public Layer
{
private:
	BulletCard*m_pSelectedItem;
	//子场景，用来保存子弹卡片
	ChooseBulletChildLayer*m_pChildLayer;
	BulletCard*m_pCurrentItem;

	ChooseBulletDelegate*m_pDelegate;
public:
	ChooseBulletLayer();
	~ChooseBulletLayer();
	CREATE_FUNC(ChooseBulletLayer);
	bool init();
public:
	virtual void chooseBullet(const Point&pos);
	bool subBulletCount();
	void setDelegate(ChooseBulletDelegate*pDelegate);
};
#endif