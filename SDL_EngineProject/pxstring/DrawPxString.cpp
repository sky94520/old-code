#include<SDL.h>
#include"SDL_PxString.h"

#define screenWidth 960
#define screenHeight 600

SDL_Window *g_pWindow = NULL;
SDL_Renderer *g_pRenderer = NULL;

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);

	g_pWindow = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		screenWidth, screenHeight, SDL_WINDOW_SHOWN);
	g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	char cursorinfo[60] = "\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB\n\xBA Cursor: \xBA\n\xC7\xC4\xC4\xC4\xC4"
		"\xC2\xC4\xC4\xC4\xC4\xB6\n\xBA  X \xB3  Y \xBA\n\xC8\xCD\xCD\xCD\xCD\xCF\xCD\xCD\xCD\xCD\xBC";

	SDL_Event e;
	bool run = true;
	while (run)
	{
		SDL_PollEvent(&e);
		switch (e.type)
		{
		case SDL_QUIT:run = false; break;
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym)
			{
			case SDLK_ESCAPE:case SDLK_AC_BACK:run = false; break;
			}
			break;
		case SDL_MOUSEMOTION:
			SDL_snprintf(cursorinfo + 37, SDL_arraysize(cursorinfo), "%4d\xB3%4d", e.motion.x, e.motion.y);
			cursorinfo[46] = '\xBA';
			break;
		}

		SDL_SetRenderDrawColor(g_pRenderer, 0, 0, 0, 0);
		SDL_RenderClear(g_pRenderer);

		ASCII_px_6x8::DrawPxString(g_pRenderer, cursorinfo, SDL_arraysize(cursorinfo), 0, 0, 4, { 255,255,255,255 });

		SDL_RenderPresent(g_pRenderer);
	}

	SDL_DestroyRenderer(g_pRenderer);
	SDL_DestroyWindow(g_pWindow);

	SDL_Quit();

	return 0;
}