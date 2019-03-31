// KeyBoard.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "KeyBoard.h"

#define MAX_LOADSTRING 100
#define _CRT_SECURE_NO_WARNNINGS

// 全局变量:
HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: 在此放置代码。
	MSG msg;
	HACCEL hAccelTable;

	// 初始化全局字符串
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_KEYBOARD, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_KEYBOARD));

	// 主消息循环:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_KEYBOARD));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_KEYBOARD);
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
   HWND hWnd;

   hInst = hInstance; // 将实例句柄存储在全局变量中

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

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
#define MAXLINE 1000
#define MAXNUMCHAR 10
	static TCHAR cCharInfo[MAXLINE][MAXNUMCHAR];
	static int nNumChar = 0;
	static int nArrayPos[MAXLINE];
	static int nX = 0,nY = 0;
	static int nLnHeight = 0;
	static int nNumLine = 0;
	static int nCharWidth = 0;
	static int nXCaret = 0,nYCaret = 0;

	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	TEXTMETRIC tm;

	switch (message)
	{
	case WM_CREATE:
		{
			hdc = GetDC(hWnd);
			//获取字体信息
			GetTextMetrics(hdc,&tm);
			//保存每行的高度和行间距
			nLnHeight = tm.tmHeight + tm.tmExternalLeading;
			//保存字符的平均宽度
			nCharWidth = tm.tmAveCharWidth;
			//创建插字符
			CreateCaret(hWnd,NULL,nCharWidth/10,tm.tmHeight);
			//显示插字符
			ShowCaret(hWnd);

			ReleaseDC(hWnd,hdc);
		}
		break;
	case WM_CHAR://非系统字符的所做的处理
		{
			if(wParam == VK_BACK)
			{
				if(nX == 0)//如果已经在一行文字的开头
				{
					if(nNumLine > 0)
					{
						nY--;
						nX = nArrayPos[nY];
					}
					else
					{
						nX = nY = nNumLine = nArrayPos[0] = 0;
						MessageBox(hWnd,L"已到文件头，不能删除字符",NULL,MB_OK);
					}
				}
				else
				{
					nArrayPos[nY] -= 1;
					//对现有字符重新调整
					for(int i=nX;i<nArrayPos[nY];i++)
						cCharInfo[nY][i] = cCharInfo[nY][i - 1];
					nX--;
				}
				//立即刷新用户区域
				InvalidateRect(hWnd,NULL,TRUE);
				break;
			}
			else if(wParam == VK_RETURN)
			{
				nNumLine++;
				if(nNumLine >= MAXLINE)
				{
					nY = nNumLine;
					MessageBox(hWnd,L"已超过最大行数",NULL,MB_OK);
					break;
				}
				nArrayPos[nY] = nX;
				//由下向上调整
				for(int i=nNumLine;i > nY + 1;i--)
				{
					
					wcscpy_s(cCharInfo[i],cCharInfo[i-1]);
					nArrayPos[i] = nArrayPos[i-1];
				}
				wcscpy_s(cCharInfo[nY + 1],&cCharInfo[nY][nX]);
				//将当前行的其余部分复制到下一行
				cCharInfo[nY][nX] ='\0';
				nY++;
				nX = 0;
				nArrayPos[nY] = _tcslen(cCharInfo[nY]);
			}
			else//其他字符
			{
				//如果当前字符没有超过限制，就插入新字符
				if(nArrayPos[nY] < MAXNUMCHAR - 1)
				{
					cCharInfo[nY][nArrayPos[nY] + 1] = '\0';
					for(int x = nArrayPos[nY];x>nX;x = x -1)
						cCharInfo[nY][x] = cCharInfo[nY][x-1];
					cCharInfo[nY][nX] = (TCHAR)wParam;
					nArrayPos[nY] += 1;
					nX++;
				}//超过
				else
				{
					nNumLine++;
					if(nNumLine > MAXLINE)
					{
						nY = nNumLine;
						MessageBox(hWnd,L"超过最大行",NULL,MB_OK);
						break;
					}
					for(int i=nNumLine;i>nY+1;i--)
					{
						wcscpy_s(cCharInfo[nY+1],cCharInfo[i-1]);
						nArrayPos[nY] = nX;
						nY++;
						nX = 0;
						nArrayPos[nY]=_tcsclen(cCharInfo[nY]);
					}
				}
				InvalidateRect(hWnd,NULL,true);
			}
		}break;
	case WM_KEYDOWN:
		{
			switch(wParam)
			{
			case VK_END:
				nX = nArrayPos[nY];
				break;
			case VK_HOME:
				nX = 0;
				break;
			case VK_DELETE:
				if(nArrayPos[nX] == nX)
				{
					MessageBox(hWnd,L"本行当前位置为空，没有字符可删除了",NULL,MB_OK);
				}
				else
				{
					for(int x = nX;x<nArrayPos[nY];x++)
					{
						cCharInfo[nY][x] = cCharInfo[nY][x-1];
						nArrayPos[nY] -= 1;
					}
				}
				break;
			case VK_LEFT:
				if(nX > 0)
					nX--;
				break;
			case VK_RIGHT:
				if(nArrayPos[nY] > nX)
					nX++;
				break;
			case VK_UP:
				if(nY > 0)
				{
					nY--;
					if(nX > nArrayPos[nY])
						nX = nArrayPos[nY];
				}
				break;
			case VK_DOWN:
				if(nY < nNumLine)
				{
					nY++;
					if(nX > nArrayPos[nY])
						nX = nArrayPos[nY];
				}
				break;

			}
			InvalidateRect(hWnd,NULL,TRUE);
		}
		break;
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
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: 在此添加任意绘图代码...
		for(int i=0;i<=nNumLine;i++)
			TextOut(hdc,0,nLnHeight*i,cCharInfo[i],nArrayPos[i]);
		SIZE size;
		GetTextExtentPoint(hdc,cCharInfo[nY],nX,&size);
		//插字符的坐标
		nXCaret = size.cx;
		nYCaret = nLnHeight*nY;
		SetCaretPos(nXCaret,nYCaret);
		
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
