#ifndef __BulletLayer_H__
#define __BulletLayer_H__
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;
class Bullet;
typedef enum BulletRoute
{
	kBulletRoute_line,
	kBulletRoute_jump
}BulletRoute;
class BulletLayer:public Layer
{
private:
	Vector<Bullet*> m_bullets;
public:
	BulletLayer();
	~BulletLayer();
	CREATE_FUNC(BulletLayer);
	bool init();

	virtual void update(float dt);
	void shootTo(const Point&startPos,const Point&endPos,const std::string&bulletName,BulletRoute route);

	Vector<Bullet*>* getBullets()
	{
		return &m_bullets;
	}
};
#endif