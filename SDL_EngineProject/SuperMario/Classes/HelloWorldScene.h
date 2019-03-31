#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
#include<string>
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;
using namespace std;

class HelloWorld : public Layer
{
private:
	float m_elpased;
public:
	HelloWorld();
	~HelloWorld();
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(HelloWorld);

	void update(float dt);
	void createLabelAtlas(const string&text,const string&charMapFle,int itemWidth,int itemHeight,unsigned int startCharMap = 0);
	void callback(Object*sender);
	void touchCallback(Object*sender,ui::TouchEventType type);
	void checkBoxCallback(Object*sender,ui::CheckBox::EventType type);
	void radioButtonCallback(Object*sender,ui::RadioButton::EventType type);
	void radioButtonGroupCallback(ui::RadioButton*r,int index,ui::RadioButtonGroup::EventType type);
};
#endif // __HELLOWORLD_SCENE_H__
