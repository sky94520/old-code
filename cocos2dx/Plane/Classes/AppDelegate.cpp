#include "AppDelegate.h"
#include "HomeScene.h"
#include "HelloWorldScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
	//设计分辨率大小
	Size designSize = Size(640,1136);
	//资源大小
	Size resourceSize = Size(640,960);
	//文件搜索路径
	std::vector<std::string> searchPaths;

    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();

	Size visibleSize = director->getVisibleSize();
	
    if(!glview) {
        glview = GLViewImpl::create("My Game");
		glview->setFrameSize(640,700);
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
	searchPaths.push_back("hd");
	//director->setContentScaleFactor(resourceSize.width/designSize.width);
	FileUtils::getInstance()->setSearchPaths(searchPaths);
	glview->setDesignResolutionSize(640,1160,ResolutionPolicy::FIXED_WIDTH);

    // create a scene. it's an autorelease object
	auto scene = HomeScene::create();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
