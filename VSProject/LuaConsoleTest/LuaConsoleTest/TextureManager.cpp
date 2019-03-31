#include "TextureManager.h"
TextureManager*TextureManager::_pInstance = nullptr;
TextureManager::TextureManager()
	:visibleSize(15,40)
{
	map = new char*[visibleSize.width];
	for(int i=0;i<visibleSize.width;++i)
		map[i] = new char[visibleSize.height];

	for(int i=0;i<visibleSize.width;i++)
	{
		for(int j=0;j<visibleSize.height;j++)
			map[i][j]= ' ';
	}
}
TextureManager::~TextureManager()
{
	for(int i=0;i<visibleSize.width;++i)
		delete[] map[i];
	delete[] map;
}
TextureManager*TextureManager::getInstance()
{
	if(_pInstance == nullptr)
	{
		_pInstance = new TextureManager();
	}
	return _pInstance;
}
void TextureManager::purge()
{
	if(_pInstance)
		delete _pInstance;
}
void TextureManager::draw(int x,int y,char ch)
{
	if(y > visibleSize.width ||
		x > visibleSize.height)
		return;
	map[y][x] = ch;
}
void TextureManager::render()
{
	
	puts("-----------------------------------------");
	for(int i=0;i<visibleSize.width;i++)
	{
		for(int j=0;j<visibleSize.height;j++)
		{
			printf("%c",map[i][j]);
			map[i][j] = ' ';
		}
		printf("#\n");
	}
	puts("-----------------------------------------");
	printf("0.退出游戏  1.背包界面  5.交互\n");
}
Size TextureManager::getVisibleSize()const
{
	return Size(visibleSize.height,visibleSize.width);
}