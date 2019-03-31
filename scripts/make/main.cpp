#include<iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

using namespace std;

SDL_Window*g_pWindow = NULL;
SDL_Renderer*g_pRendener = NULL;

int main(int argc,char* argv[])
{
	SDL_Texture*tex = NULL;
	SDL_Init(SDL_INIT_VIDEO);
	g_pWindow = SDL_CreateWindow("test",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,640,480,SDL_WINDOW_SHOWN);
	g_pRendener = SDL_CreateRenderer(g_pWindow,-1,0);
	SDL_SetRenderDrawColor(g_pRendener,255,0,255,255);
	tex = IMG_LoadTexture(g_pRendener,"loading_01.png");
	SDL_RenderClear(g_pRendener);
	//
	SDL_RenderCopy(g_pRendener,tex,NULL,NULL);
	SDL_RenderPresent(g_pRendener);
	SDL_Delay(2000);
	return 0;
}
