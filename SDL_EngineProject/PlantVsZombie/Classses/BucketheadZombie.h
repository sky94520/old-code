#ifndef __BucketheadZombie_H__
#define __BucketheadZombie_H__
#include<string>
#include "ConeheadZombie.h"
using namespace std;

class BucketheadZombie : public ConeheadZombie
{
public:
	BucketheadZombie();
	~BucketheadZombie();
	static BucketheadZombie*create(const string&zombieName);
	bool init(const string&zombieName);
	virtual void onGarnishryDead();
protected:
	virtual void judgeInnerSpritePos();
};
#endif