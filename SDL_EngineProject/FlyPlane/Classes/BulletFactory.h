#ifndef __BulletFactory_H__
#define __BulletFactory_H__
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;

typedef enum BulletType
{
	kBulletType_Common,/*ÆÕÍ¨×Óµ¯*/
}BulletType;
class Bullet;

class BulletFactory:public Object
{
public:
	BulletFactory();
	virtual ~BulletFactory();
	CREATE_FUNC(BulletFactory);
	bool init();

	Bullet*orderBullet(BulletType type);
	virtual Bullet*createBullet(BulletType type);
};
#endif