#ifdef _MSC_VER
#include"Codes\UseUTF-8.h"
#include"Codes\UseVisualStyle.h"
#endif

#include<SDL.h>
#include<memory>
#include"MySDL2.h"

int main(int argc, char *argv[])
{
	std::unique_ptr<SDL_Window, void(*)(SDL_Window*)>pWindow(nullptr, SDL_DestroyWindow);
	std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)>pRenderer(nullptr, SDL_DestroyRenderer);
	int fullscreen = 0, mouseX = 0, mouseY = 0;
	int screenWidth = 960, screenHeight = 600, wrapLength = 32, pxSize = 4;

	SDL_Init(SDL_INIT_EVERYTHING);

	pWindow.reset(SDL_CreateWindow("PxString", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight,
		SDL_WINDOW_SHOWN));
	pRenderer.reset(SDL_CreateRenderer(pWindow.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));

	SDL_SetRenderDrawBlendMode(pRenderer.get(), SDL_BLENDMODE_ADD);
	
	SDL_Rect windowRect = { 0 };
	SDL_GetWindowSize(pWindow.get(), &windowRect.w, &windowRect.h);

	SDL_Event e;
	bool run = true;
	while (run)
	{
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_QUIT:run = false; break;
			case SDL_KEYDOWN:
				switch (e.key.keysym.sym)
				{
				case SDLK_ESCAPE:case SDLK_AC_BACK:
					run = false;
					break;
				case SDLK_F11:
					fullscreen ^= SDL_WINDOW_FULLSCREEN_DESKTOP;
					SDL_SetWindowFullscreen(pWindow.get(), fullscreen);
					break;
				}
				break;
			case SDL_MOUSEWHEEL:
				switch (e.wheel.y&0x80000000)
				{
				case 0x00000000:pxSize = SDL_min(pxSize + 1, 10); break;
				case 0x80000000:pxSize = SDL_max(pxSize - 1, 1); break;
				}
				break;
			}
		}

		SDL_SetRenderDrawColor(pRenderer.get(), 0, 0, 0, 0);
		SDL_RenderClear(pRenderer.get());
		SDL_SetRenderDrawColor(pRenderer.get(), 255, 255, 255, 255);

		for (int i = 0; i <= 256; i++)
		{
			using namespace MySDL2::ASCII_px_6x8;
			DrawPxChar(pRenderer.get(), i, i % wrapLength * px_count_horizonal * pxSize,
				i / wrapLength * px_count_vertical * pxSize, pxSize);
		}

		SDL_RenderPresent(pRenderer.get());
	}

	SDL_Quit();

	return 0;
}