#ifndef __TextureManager_H__
#define __TextureManager_H__
#include<cstdio>
#include "Size.h"
class TextureManager
{
private:
	char ** map;
	Size visibleSize;
	static TextureManager*_pInstance;
private:
	TextureManager();
	~TextureManager();
public:
	static TextureManager*getInstance();
	void purge();
	//由各个类调用，使产生图形
	void draw(int x,int y,char ch);
	//绘制图形
	void render();
	Size getVisibleSize()const;//获取地图大小 
};
#endif