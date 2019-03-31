#include<iostream>

#include "SDL2/SDL.h"
#include "TMXTiledMap.h"
using namespace std;
//全局常量
const int FPS = 60;
const int DELAY_TIME = 1000.0f/FPS;

int main(int argc,char**argv)
{
    SDL_Window*win = NULL;
    SDL_Renderer*ren = NULL;
    //
    Uint32 frameStart,frameTime;
    //
    SDL_Event event;
    //
    bool running = true;
    TMXTiledMap*tileMap;
    /*SDL_INIT_HAPIIC有的可能不存在在，如在普通电脑中*/
    if (SDL_Init(
                SDL_INIT_EVERYTHING
#ifndef __linux
                ^SDL_INIT_HAPTIC
#endif
            ) >= 0)
    {
        if((win = SDL_CreateWindow("TileMapTest", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480,SDL_WINDOW_SHOWN)) == NULL)
        {
            cout<<"error:"<<SDL_GetError()<<endl;
            return -1;
        }
        else if((ren = SDL_CreateRenderer(win, -1, 0)) == NULL)
        {
            cout<<"error:"<<SDL_GetError()<<endl;
            return -2;
        }

        SDL_SetRenderDrawColor(ren,210,250,255,255);
    }
    tileMap = new TMXTiledMap("assets/map1.tmx",ren);
    //
    while(running)
    {
        frameStart = SDL_GetTicks();

        SDL_RenderClear(ren);
        //add code here..
        tileMap->Draw();
        SDL_RenderPresent(ren);

        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
                running = false;
        }
        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < DELAY_TIME)
        {
            SDL_Delay(int(DELAY_TIME - frameTime));
        }
    }
    return 0;
}
