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
	//�ɸ�������ã�ʹ����ͼ��
	void draw(int x,int y,char ch);
	//����ͼ��
	void render();
	Size getVisibleSize()const;//��ȡ��ͼ��С 
};
#endif