#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
#include<string>
#include "SDL_Engine/SDL_Engine.h"
#include "Box2D.h"
using namespace SDL;
using namespace std;

class GoldCounter;
class ScrollLabel;

class HelloWorld : public Layer
{
private:
	ui::Button*m_pStartBtn;
	ui::Button*m_pHelpBtn;
	ui::Button*m_pExitBtn;
	ui::CheckBox*m_pMusicBtn;
	ui::CheckBox*m_pEffectBtn;
	LabelAtlas*m_pLabel;
	LabelAtlas*m_pLabel2;
	b2World*m_pWorld;
public:
	HelloWorld();
	~HelloWorld();
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(HelloWorld);
	virtual void update(float dt);
private:
	bool onTouchBegan(Touch*touch,SDL_Event*event);
	void onTouchMoved(Touch*touch,SDL_Event*event);
	void onTouchEnded(Touch*touch,SDL_Event*event);
	void touchCallback(Object*,ui::TouchEventType);
	void touchTest(Object*sender);
};
#endif // __HELLOWORLD_SCENE_H__
