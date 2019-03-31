#include "TextureManager.h"
TextureManager*TextureManager::m_pInstance = nullptr;
TextureManager::TextureManager()
	:m_compatibleDC(NULL),m_bufDC(NULL)
	,m_hWnd(NULL)
{
}
TextureManager::~TextureManager()
{
	for(auto iter = m_textureMap.begin();iter != m_textureMap.end();)
	{
		auto bitmap = iter->second;
		iter = m_textureMap.erase(iter);
		DeleteObject(bitmap);
	}
	//关闭兼容环境设备
	DeleteDC(m_bufDC);
	m_bufDC = NULL;

	DeleteDC(m_compatibleDC);
	m_bufDC = NULL;
}
TextureManager*TextureManager::getInstance()
{
	if(m_pInstance == nullptr)
	{
		m_pInstance = new TextureManager();
	}
	return m_pInstance;
}
BOOL TextureManager::init(HWND hWnd)
{
	m_hWnd = hWnd;

	HDC hdc = GetDC(hWnd);
	//创建兼容设备的内存环境DC
	m_compatibleDC = CreateCompatibleDC(hdc);
	m_bufDC = CreateCompatibleDC(hdc);
	RECT r;
	GetClientRect(hWnd,&r);
	//创建bmp
	HBITMAP bitmap = CreateCompatibleBitmap(hdc,r.right-r.left,r.bottom-r.top);
	SelectObject(m_compatibleDC,bitmap);

	ReleaseDC(hWnd,hdc);

	return TRUE;
}
void TextureManager::purge()
{
	if(m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}
BOOL TextureManager::load(LPCWSTR filename,LPCWSTR id)
{
	//判断是否存在对应id
	if(m_textureMap.find(id) != m_textureMap.end())
	{
		wprintf(L"the bmp is already loaded!\n");
		return false;
	}
	//加载
	HBITMAP sprite = (HBITMAP)LoadImage(NULL,filename,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	//添加
	m_textureMap.insert(make_pair(id,sprite));
	return TRUE;
}
BOOL TextureManager::transparentBlt(LPCWSTR id,int xDest,int yDest,int wDest,int hDest,int xSrc,int ySrc,int wSrc,int hSrc,UINT transparent)
{
	//从内存中找到人物图
	auto iter = m_textureMap.find(id);
	if(iter == m_textureMap.end())
	{
		return FALSE;
	}
	HBITMAP bitmap = iter->second;

	SelectObject(m_bufDC,bitmap);

	return ::TransparentBlt(m_compatibleDC,xDest,yDest,wDest,hDest,m_bufDC,xSrc,ySrc,wSrc,hSrc,transparent);
}
BOOL TextureManager::bitBlt(LPCWSTR id,int xDest,int yDest,int wDest,int hDest,int xSrc,int ySrc,DWORD rop)
{
	//从内存中找到人物图
	auto iter = m_textureMap.find(id);
	if(iter == m_textureMap.end())
	{
		return FALSE;
	}
	HBITMAP bitmap = iter->second;

	SelectObject(m_bufDC,bitmap);
	
	return ::BitBlt(m_compatibleDC,xDest,yDest,wDest,hDest,m_bufDC,xSrc,ySrc,rop);
}
BOOL TextureManager::textOut(int x,int y,LPCWSTR text,int count,COLORREF color)
{
	SetTextColor(m_compatibleDC,color);
	return ::TextOut(m_compatibleDC,x,y,text,count);
}
int TextureManager::drawText(LPCWSTR text,int count,LPRECT lpRect,UINT format,COLORREF color)
{
	SetTextColor(m_compatibleDC,color);
	return ::DrawText(m_compatibleDC,text,count,lpRect,format);
}
int TextureManager::setBkMode(int iBkMode)
{
	return ::SetBkMode(m_compatibleDC,iBkMode);
}
BOOL TextureManager::getTextMetrics(TEXTMETRIC*tm)
{
	return ::GetTextMetrics(m_compatibleDC,tm);
}
RECT TextureManager::getClientRect()
{
	RECT r;
	BOOL ret = GetClientRect(m_hWnd,&r);
	return r;
}
void TextureManager::draw(HDC hdc)
{
	//默认绘制全屏
	RECT rect;
	GetClientRect(m_hWnd,&rect);
	//BitBlt(hdc,0,0,rect.right-rect.left,rect.bottom-rect.top,m_bufDC,0,0,SRCCOPY);
	
	BitBlt(hdc,0,0,rect.right-rect.left,rect.bottom-rect.top,m_compatibleDC,0,0,SRCCOPY);
}