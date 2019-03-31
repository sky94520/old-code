#include "Game.h"
#include "TextureManager.h"
#include "BackgroundLayer.h"

Game::Game()
	:m_pBackgroundLayer(nullptr)
{
}
Game::~Game()
{
}
BOOL Game::gameInit(HWND hWnd)
{
	TextureManager::getInstance()->init(hWnd);
	//加载并初始化资源
	m_pBackgroundLayer = new BackgroundLayer();
	m_pBackgroundLayer->load(L"assets\\bg.bmp");

	return TRUE;
}
void Game::gamePaint(HWND hWnd)
{
	RECT r;
	GetClientRect(hWnd,&r);

	HDC hdc = GetDC(hWnd);

	int w = r.right - r.left;
	int h = r.bottom - r.top;
	//贴入背景
	m_pBackgroundLayer->draw();

	TextureManager::getInstance()->draw(hdc);

	ReleaseDC(hWnd,hdc);
}
void Game::gameUpdate(HWND hWnd)
{
	m_pBackgroundLayer->update();
}
BOOL Game::gameCleanup(HWND hWnd)
{
	m_pBackgroundLayer->clean();

	return TRUE;
}
void Game::gameMouseMotion(WORD x,WORD y)
{
}
void Game::gameMouseBtn(WORD x,WORD y)
{
}