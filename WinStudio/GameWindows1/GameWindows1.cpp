// GameWindows1.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "GameWindows1.h"

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define FPS 60
//个人全局变量
HWND g_hWnd = NULL;
HDC g_mdc = NULL;//兼容设备环境句柄

HBITMAP g_hBackground = NULL;
HBITMAP g_hSprite = NULL;//将要渲染的图片
float g_fPre = 0.f;
int g_nNum = 0;

// 此代码模块中包含的函数的前向声明:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
//个人函数
bool gameInit(HWND hWnd);
void gamePaint(HWND hWnd);
void gameCleanup(HWND hWnd);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: 在此放置代码。
	MSG msg = {0};
	HACCEL hAccelTable;

	// 初始化全局字符串
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_GAMEWINDOWS1, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GAMEWINDOWS1));

	// 主消息循环:
	while(msg.message != WM_QUIT)
	{
		if(PeekMessage(&msg,0,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			float now = GetTickCount();
			//到了渲染时间
			if(now - g_fPre >= FPS)
			{
				gamePaint(g_hWnd);
				g_fPre = now;
			}
		}
	}
	return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GAMEWINDOWS1));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_GAMEWINDOWS1);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

   g_hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, WINDOW_WIDTH, WINDOW_HEIGHT, NULL, NULL, hInstance, NULL);

   if (!g_hWnd)
   {
      return FALSE;
   }
   //个人函数
   gameInit(g_hWnd);

   ShowWindow(g_hWnd, nCmdShow);
   UpdateWindow(g_hWnd);

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的: 处理主窗口的消息。
//
//  WM_COMMAND	- 处理应用程序菜单
//  WM_PAINT	- 绘制主窗口
//  WM_DESTROY	- 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// 分析菜单选择:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			gameCleanup(hWnd);
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: 在此添加任意绘图代码...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
bool gameInit(HWND hWnd)
{
	//获取设备环境句柄
	HDC hdc = GetDC(hWnd);
	//加载图片资源
	wchar_t filename[20];
	//载入位图
	g_hBackground = (HBITMAP)LoadImage(NULL,L"bg.bmp",IMAGE_BITMAP,WINDOW_WIDTH,WINDOW_HEIGHT,LR_LOADFROMFILE);
	g_hSprite = (HBITMAP)LoadImage(NULL,L"goright.bmp",IMAGE_BITMAP,480,108,LR_LOADFROMFILE);
	//创建兼容DC
	g_mdc = CreateCompatibleDC(hdc);

	ReleaseDC(hWnd,hdc);
	
	return TRUE;
}
void gamePaint(HWND hWnd)
{
	HDC hdc = GetDC(hWnd);
	//选用位图对象
	g_nNum = (g_nNum++)%8;
	//绘制背景
	SelectObject(g_mdc,g_hBackground);
	BitBlt(hdc,0,0,WINDOW_WIDTH,WINDOW_HEIGHT,g_mdc,0,0,SRCCOPY);
	//绘制人物
	TransparentBlt(hdc,50,50,60,108,g_mdc,g_nNum*60,0,60,108,RGB(255,0,0));
	ReleaseDC(hWnd,hdc);
}
void gameCleanup(HWND hWnd)
{
	//释放资源对象
	//DeleteObject(g_bitmap);
	DeleteDC(g_mdc);
}