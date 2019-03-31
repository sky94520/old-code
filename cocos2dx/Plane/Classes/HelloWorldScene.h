#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "GLES-Render.h"
#define PTM_RATIO 32
USING_NS_CC;
class HelloWorld : public cocos2d::Layer,public b2ContactListener
{
private:
	b2World*world;
	GLESDebugDraw*m_debugDraw;
public:
	HelloWorld();
	~HelloWorld();
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(HelloWorld);
	virtual void update(float dt);
	void initPhysics();

	virtual void BeginContact(b2Contact* contact);
	/// Called when two fixtures cease to touch.
	virtual void EndContact(b2Contact* contact);

	virtual bool onTouchBegan(Touch *touch, Event *unused_event); 
	virtual void draw(Renderer *renderer, const Mat4& transform, uint32_t flags);
private:
	void addNewSpriteAtPosition(Vec2 pos);

	void onDraw(const kmMat4 &transform,bool transformUpdated);
	CustomCommand _customCommand;
};

#endif // __HELLOWORLD_SCENE_H__
