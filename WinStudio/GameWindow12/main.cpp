#include<windows.h>
#include "Game.h"

//解决 TransparentBlt
#pragma comment(lib,"msimg32.lib")
//全局变量
HWND hWnd = NULL;
HACCEL hAccelector = NULL;
DWORD g_lPre = 0L;
Game*gameEngine = nullptr;

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define FPS 60

BOOL InitWindowClass(HINSTANCE hInstance,int nCmdShow);
LRESULT CALLBACK WndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam);

//void handleMenuMessage(UINT message, WPARAM wParam,LPARAM lParam);
//主函数
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	MSG msg={0};

	if(InitWindowClass(hInstance,nCmdShow) == false)
	{
		MessageBox(NULL,L"创建窗口失败！",L"创建窗口",NULL);
		return -1;
	}
	gameEngine = new Game();
	//游戏资源初始化
	if(gameEngine->gameInit(hWnd) == false)
	{
		MessageBox(NULL,L"游戏资源加载！",L"资源加载",NULL);
		return -1;
	}
	hAccelector = (HACCEL)LoadAccelerators(hInstance,L"Menu");
	/*while(GetMessage(&msg,NULL,0,0))
	{
		if(TranslateAccelerator(hWnd,hAccelector,&msg) == false)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}*/
	// 主消息循环:
	while(msg.message != WM_QUIT)
	{
		if(PeekMessage(&msg,0,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		DWORD now = GetTickCount();
		//到了渲染时间
		if(now - g_lPre >= FPS)
		{
			gameEngine->gamePaint(hWnd);
			gameEngine->gameUpdate(hWnd);
			g_lPre = now;
		}
	}
	return (int)msg.wParam;
}
BOOL InitWindowClass(HINSTANCE hInstance,int nCmdShow)
{
	WNDCLASSEX wcex;

	TCHAR szWindowClass[] = L"12";
	TCHAR szTitle[] = L"12";
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = 0;
	wcex.lpfnWndProc = WndProc;//事件响应函数
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance,MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL,IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcex.lpszMenuName = L"MyMenuName";
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance,MAKEINTRESOURCE(IDI_APPLICATION));
	//注册
	if(RegisterClassEx(&wcex) == false)
		return FALSE;
	hWnd = CreateWindow(szWindowClass,szTitle,WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,
		WINDOW_WIDTH,WINDOW_HEIGHT,NULL,NULL,hInstance,NULL);
	
	if(hWnd == NULL)
		return FALSE;
	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}
LRESULT CALLBACK WndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	switch(message)
	{
	case WM_COMMAND:
		//handleMenuMessage(message,wParam,lParam);
		break;
	case WM_DESTROY:
		gameEngine->gameCleanup(hWnd);
		PostQuitMessage(0);
		break;
	case WM_MOUSEMOVE:
		//接受鼠标移动信息并传递给Game
		{
			WORD x = LOWORD(lParam);
			WORD y = HIWORD(lParam);
			gameEngine->gameMouseMotion(x,y);
		}
		break;
		//发送鼠标左键按下信息
	case WM_LBUTTONDOWN:
		{
			WORD x = LOWORD(lParam);
			WORD y = HIWORD(lParam);
			gameEngine->gameMouseBtn(x,y);
		}
		break;
	default:
		return DefWindowProc(hWnd,message,wParam,lParam);
	}
	return 0;
}
/*void handleMenuMessage(UINT message,WPARAM wParam,LPARAM lParam)
{
	HMENU hMenu = NULL;
	HMENU hAddMenu = NULL;

	switch(LOWORD(wParam))
	{
	case IDM_ADDMENU:
		hMenu = GetMenu(hWnd);
		hAddMenu = CreateMenu();
		//添加菜单项
		AppendMenu(hAddMenu,MF_ENABLED,IDM_qiuhe,L"求和");
		AppendMenu(hAddMenu,MF_ENABLED,IDM_fangcha,L"方差");
		AppendMenu(hAddMenu,MF_ENABLED,IDM_pingjunzhi,L"平均值");
		AppendMenu(hAddMenu,MF_ENABLED,IDM_junfanggen,L"均方根");
		//插入到主菜单
		InsertMenu(hMenu,2,MF_POPUP|MF_BYPOSITION,(UINT)hAddMenu,L"统计计算(&C)");
		//相应改变菜单中有关绘图统计计算菜单项的内容
		EnableMenuItem(hMenu,IDM_ADDMENU,MF_GRAYED);
		EnableMenuItem(hMenu,IDM_DELMENU,MF_ENABLED);
		//重新显示窗口菜单
		DrawMenuBar(hWnd);
		break;
	case IDM_DELMENU:
		hMenu = GetMenu(hWnd);
		DeleteMenu(hMenu,2,MF_BYPOSITION);
		//改变对应菜单项的属性
		EnableMenuItem(hMenu,IDM_ADDMENU,MF_ENABLED);
		EnableMenuItem(hMenu,IDM_DELMENU,MF_GRAYED);
		DrawMenuBar(hWnd);
		break;
	case IDM_EXIT:
		SendMessage(hWnd,WM_DESTROY,0,0);//向应用程序发送结束信息
		break;
	}
}*/