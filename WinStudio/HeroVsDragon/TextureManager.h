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
	map<LPCWSTR,HBITMAP> m_textureMap;//����ͼƬ
	static TextureManager*m_pInstance;

	HDC m_compatibleDC;//������ 2
	HDC m_bufDC;//������ 3

	HWND m_hWnd;
private:
	TextureManager();
	~TextureManager();
public:
	static TextureManager*getInstance();
	BOOL init(HWND hWnd);
	void purge();
	//���ض�ӦͼƬ��������id
	BOOL load(LPCWSTR filename,LPCWSTR id);
	BOOL transparentBlt(LPCWSTR id,int xDest,int yDest,int wDest,int hDest,int xSrc,int ySrc,int wSrc,int hSrc,UINT transparent);
	BOOL bitBlt(LPCWSTR id,int xDest,int yDest,int wDest,int hDest,int xSrc,int ySrc,DWORD rop);
	BOOL textOut(int x,int y,LPCWSTR text,int count,COLORREF color);
	int drawText(LPCWSTR text,int count,LPRECT lpRect,UINT format,COLORREF color);
	//���ñ���ģʽ Ĭ����opaque
	int setBkMode(int iBkMode);
	//��ȡ������Ϣ
	BOOL getTextMetrics(TEXTMETRIC* tm);
	//���Ƶ���Ļ
	void draw(HDC hdc);
};
#endif
