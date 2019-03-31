//#include "SDL2/SDL.h"

#ifndef __Director_H__
#define __Director_H__

/**导演类
主要功能 创建窗口，渲染器
该类依赖于SDL.h
*/
class Director
{
private:
	SDL_Window*mWin;
	SDL_Renderer*mRen;
	static Director*mDirector;
	//窗口大小，在手机上为分辨率大小
	SDL_Rect winSize;
public:
    static Director*getInstance();
    static void init();
    SDL_Renderer * getRenderer() const;
    Director();
    ~Director();

    SDL_Rect getVisibleSize();
};
//class end
Director*Director::mDirector = NULL;

//对窗口进行初始化
Director::Director()
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

	mWin = SDL_CreateWindow("game",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,320,480,SDL_WINDOW_SHOWN);
	mRen = SDL_CreateRenderer(mWin,-1,SDL_RENDERER_PRESENTVSYNC);
	//获得窗口大小
	winSize.x = 0;
	winSize.y = 0;
	SDL_GetWindowSize(mWin,&winSize.w,&winSize.h);
}
void Director::init()
{
    if (mDirector == NULL)
    {
        mDirector = new Director();
    }
}
Director::~Director()
{
	SDL_DestroyRenderer(mRen);
	SDL_DestroyWindow(mWin);

}
Director*Director::getInstance()
{
	if (mDirector == NULL)
	{
		//调用构造器
		mDirector = new Director();
	}
	return mDirector;
}
SDL_Renderer*Director::getRenderer() const
{
	return this->mRen;
}
SDL_Rect Director::getVisibleSize()
{
	return winSize;
}
#endif
