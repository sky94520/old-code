#ifndef __Fps_H__
#define __Fps_H__

#include<sstream>
#include<stdexcept>

#include "SDL2/SDL.h"
#include "Timer.h"

class Fps
{
 private:
    //限制的帧数 默认为60
    const int m_nFrame;
    //计时器
    Timer m_capTimer;
    Timer m_fpsTimer;
    //上一秒运行的帧数
    int m_nLastFrame;
    //当前帧数
    int m_nCurFrame;
    //
    SDL_Texture*m_tShowFPS;
 public:
    Fps(int frame = 60);
    //更新fps
    void update();
    //render to the screen
    void draw(SDL_Renderer*ren);
};
#endif
