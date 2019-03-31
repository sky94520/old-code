#ifndef __BulletLayer_H__
#define __BulletLayer_H__
#include<vector>
#include "SDL_Engine/SDL_Engine.h"
#include "BulletFactory.h"

using namespace SDL;
using namespace std;
class Bullet;
class Plane;

class BulletLayer:public Layer
{
private:
	vector<Bullet*> m_bullets;
	BulletFactory*m_pFactory;
public:
	BulletLayer();
	~BulletLayer();
	CREATE_FUNC(BulletLayer);
	bool init();

	virtual void update(float dt);
	//提供给外界的接口
	void shooting(Plane*plane,BulletType type);
	void reset();
};
#endif