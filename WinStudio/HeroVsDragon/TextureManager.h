#ifndef __TextureManager_H__
#define __TextureManager_H__
#include<Windows.h>
#include<tchar.h>
#include<map>
#include<string>

using namespace std;

class TextureManager
{
private:
	map<LPCWSTR,HBITMAP> m_textureMap;//保存图片
	static TextureManager*m_pInstance;

	HDC m_compatibleDC;//缓冲区 2
	HDC m_bufDC;//三缓冲 3

	HWND m_hWnd;
private:
	TextureManager();
	~TextureManager();
public:
	static TextureManager*getInstance();
	BOOL init(HWND hWnd);
	void purge();
	//加载对应图片，并设置id
	BOOL load(LPCWSTR filename,LPCWSTR id);
	BOOL transparentBlt(LPCWSTR id,int xDest,int yDest,int wDest,int hDest,int xSrc,int ySrc,int wSrc,int hSrc,UINT transparent);
	BOOL bitBlt(LPCWSTR id,int xDest,int yDest,int wDest,int hDest,int xSrc,int ySrc,DWORD rop);
	BOOL textOut(int x,int y,LPCWSTR text,int count,COLORREF color);
	int drawText(LPCWSTR text,int count,LPRECT lpRect,UINT format,COLORREF color);
	//设置背景模式 默认是opaque
	int setBkMode(int iBkMode);
	//获取字体信息
	BOOL getTextMetrics(TEXTMETRIC* tm);
	//绘制到屏幕
	void draw(HDC hdc);
};
#endif
