#include<cstring>
#pragma once
//定义默认字体大小
#define UNDEFINED_FONT_SIZE 25
class Font
{
	private:
	TTF_Font*m_font;
	SDL_Renderer*m_ren;

public:
	Font();
	Font(int fontSize);
	~Font();
	int printText(const char*str,SDL_Point position,SDL_Color color);
	//绑定渲染器
	void bindRenderer(SDL_Renderer*ren);
};
Font::Font()
{
	m_ren = NULL;
	if (TTF_WasInit() != 1)
	TTF_Init();

	m_font = TTF_OpenFont("/Resources/DroidSansFallback.ttf",UNDEFINED_FONT_SIZE);
}
Font::Font(int fontSize)
{
	m_ren = NULL;
	if (TTF_WasInit() != 1)
	TTF_Init();

	m_font = TTF_OpenFont("/Resources/DroidSansFallback.ttf",fontSize);
	TTF_SetFontStyle(m_font,TTF_STYLE_NORMAL);
}
Font::~Font()
{
	TTF_CloseFont(m_font);
	TTF_Quit();
}
void Font::bindRenderer(SDL_Renderer*ren)
{
	this->m_ren = ren;
}
int Font::printText(const char*str,SDL_Point position,SDL_Color color)
{
	if (m_ren == NULL)
	return -1;
	SDL_Surface*sur = NULL;
	SDL_Texture*tex = NULL;
	//矩形
	SDL_Rect rect = {position.x,position.y,0,0};
	//获得字符串的适宜宽高度
	//TTF_SizeText(m_font,str,&rect.w,&rect.h);

	sur = TTF_RenderUTF8_Blended(m_font,str,color);
	tex = SDL_CreateTextureFromSurface(m_ren,sur);
	SDL_QueryTexture(tex,0,0,&rect.w,&rect.h);
	SDL_RenderCopy(m_ren,tex,0,&rect);

	SDL_FreeSurface(sur);
	SDL_DestroyTexture(tex);
}
