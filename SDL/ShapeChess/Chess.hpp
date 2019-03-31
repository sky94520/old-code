#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#pragma once
/* 依赖库。SDL */
// 棋盘上可能出现的棋子
enum CHESS_TYPE
{ CHESS_NONE, CHESS_X, CHESS_O, CHESS_OX };

class Chess
{
  public:
	// 棋盘
	CHESS_TYPE m_map[3][3];
	private:
	// 判断谁赢了
	CHESS_TYPE chess_win;
	// 判断这一次是谁下棋子
	bool chess_type;
	// 棋子形状
	SDL_Texture *chessTex[2];
	SDL_Rect chessRect;
	// 绑定渲染器
	SDL_Renderer *ren;
	// 背景
	SDL_Texture *bg;
	// 屏幕分辨率
	int w;
	int h;
  public:
	  Chess();
	 ~Chess();
	CHESS_TYPE isEnd();
	void bindRenderer(SDL_Renderer * ren);
	void draw();
	// 设置分辨率大小
	void setDPI(int w, int h);
	// 接收并且处理按键(逻辑)
	void handleEvent(SDL_Event event);
};

Chess::Chess()
{
	w = 0;
	h = 0;
	chess_type = false;
	chess_win = CHESS_NONE;
	ren = NULL;
	// 初始化棋盘
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			m_map[i][j] = CHESS_NONE;
}

Chess::~Chess()
{
	SDL_DestroyTexture(chessTex[0]);
	SDL_DestroyTexture(chessTex[1]);
}

CHESS_TYPE Chess::isEnd()
{
	return chess_win;
}

void Chess::bindRenderer(SDL_Renderer * ren)
{
	this->ren = ren;

	bg = IMG_LoadTexture(ren, "Resources/bg3.jpg");
	//返回0成功
/*	SDL_SetTextureBlendMode(bg,SDL_BLENDMODE_MOD);
	SDL_SetTextureAlphaMod(bg,125);*/
}

void Chess::setDPI(int w, int h)
{
	this->w = w;
	this->h = h;
	/* 获得棋子图片 */
	if (TTF_WasInit() != 1)
		TTF_Init();
	// 获得匹配的字体大小
	TTF_Font *font = TTF_OpenFont("/system/fonts/DroidSansFallback.ttf", w / 3);

	SDL_Surface *sur = NULL;

	chessRect.x = 0;
	chessRect.y = 0;
	chessRect.w = w / 3;
	chessRect.h = w / 3;

	SDL_Color color = { 125, 32, 199 };
	// X
	sur = TTF_RenderUTF8_Blended(font, "X", color);
	chessTex[0] = SDL_CreateTextureFromSurface(ren, sur);
	SDL_FreeSurface(sur);
	// O
	sur = TTF_RenderUTF8_Blended(font, "0", color);
	chessTex[1] = SDL_CreateTextureFromSurface(ren, sur);
	SDL_FreeSurface(sur);
	// 关闭字体
	TTF_CloseFont(font);
}

void Chess::draw()
{
	if (ren == NULL)
		return;
	// draw
	// SDL_SetRenderDrawColor(ren, 255, 0, 0, 0);
	// 目前只考虑竖屏
	SDL_RenderCopy(ren, bg, NULL, NULL);
	// 横线
	SDL_RenderDrawLine(ren, 0, w / 3, w, w / 3);
	SDL_RenderDrawLine(ren, 0, w / 3 * 2, w, w / 3 * 2);
	SDL_RenderDrawLine(ren, 0, w, w, w);
	// SDL_RenderDrawLine(ren, 0, w/3 * 4, w, w/3 * 4);
	// 竖线
	SDL_RenderDrawLine(ren, w / 3, 0, w / 3, w);
	SDL_RenderDrawLine(ren, w / 3 * 2, 0, w / 3 * 2, w);
	// SDL_RenderFillRect(ren,&chessRect);
	// 画出棋子
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
		{
			if (m_map[i][j] != CHESS_NONE)
			{
				chessRect.x = i * w / 3;
				chessRect.y = j * w / 3;
				SDL_RenderCopy(ren, chessTex[m_map[i][j] - 1], 0, &chessRect);
			}
		}
}

void Chess::handleEvent(SDL_Event event)
{
	int x = 0, y = 0;
	if (event.type == SDL_FINGERDOWN)
	{
		x = event.tfinger.x * this->w;
		y = event.tfinger.y * this->h;
		// 避免数组越界
		if (y >= w)
			return;
		x = x / (w / 3) >= 2 ? 2 : x / (w / 3);
		y = y / (w / 3) >= 2 ? 2 : y / (w / 3);

		if (m_map[x][y] == CHESS_NONE)
		{
			if (chess_type  == false )
				m_map[x][y] = CHESS_O;
			else
				m_map[x][y] = CHESS_X;

			chess_type = chess_type == true?false:true;
		}
	}
	/* 逻辑判断 */
	// 横
	/*if (m_map[0][i] == m_map[1][i] && m_map[1][i] == m_map[2][i])
	可能会是三个全是CHESS_NONE*/
	for (int i = 0; i < 3; i++)
		if (m_map[0][i] != CHESS_NONE && m_map[0][i] == m_map[1][i] && m_map[1][i] == m_map[2][i])
		{
			chess_win = m_map[1][i];
			 return;
		}
	// 竖
	for (int i = 0; i < 3; i++)
		if (m_map[i][0] != CHESS_NONE && m_map[i][0] == m_map[i][1] && m_map[i][1] == m_map[i][2])
		{
			chess_win = m_map[i][0];
			return;
		}
	if (m_map[0][0] != CHESS_NONE && m_map[0][0] == m_map[1][1] && m_map[1][1] == m_map[2][2])
	{
		chess_win = m_map[0][0];
		return;
	}
	if (m_map[2][0] != CHESS_NONE && m_map[2][0] == m_map[1][1] && m_map[1][1] == m_map[0][2])
	{
		chess_win = m_map[2][0];
		return;
	}
	// 平局判断
	chess_win = CHESS_OX;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
		{
			if (m_map[i][j] == CHESS_NONE)
			{
				chess_win = CHESS_NONE;
				return;
			}
		}
}
