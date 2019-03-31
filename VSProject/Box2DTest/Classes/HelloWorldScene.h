#ifndef __HelloWorld_H__
#define __HelloWorld_H__
#include "Box2D/Box2D.h"
#include "SDL_Engine/SDL_Engine.h"
#include "lua/lua.h"
using namespace SDL;
#define PTM_RATIO 32
class DebugDraw;

class HelloWorld:public Layer,b2ContactListener
{
private:
	b2World*m_pWorld;
	DebugDraw*m_pDebugDraw;
public:
	HelloWorld();
	~HelloWorld();
	CREATE_FUNC(HelloWorld);
	static Scene*createScene();
	bool init();
	virtual void update(float dt);
	virtual bool onTouchBegan(Touch*,SDL_Event*);
private:
	void initPhysics();

	void BeginContact(b2Contact*contact);
};
#endif