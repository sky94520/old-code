#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
#include<vector>
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;

class HelloWorld : public Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(Object* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
	//virtual bool onTouchBegan(SDL::Touch*,SDL_Event*);
	void onTouchesBegan(std::vector<SDL::Touch*>,SDL_Event*);
	void onTouchesMoved(std::vector<SDL::Touch*>,SDL_Event*);
	void onTouchesEnded(std::vector<SDL::Touch*>,SDL_Event*);
};

#endif // __HELLOWORLD_SCENE_H__
