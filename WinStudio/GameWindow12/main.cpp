#include<windows.h>
#include "Game.h"

//��� TransparentBlt
#pragma comment(lib,"msimg32.lib")
//ȫ�ֱ���
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
//������
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	MSG msg={0};

	if(InitWindowClass(hInstance,nCmdShow) == false)
	{
		MessageBox(NULL,L"��������ʧ�ܣ�",L"��������",NULL);
		return -1;
	}
	gameEngine = new Game();
	//��Ϸ��Դ��ʼ��
	if(gameEngine->gameInit(hWnd) == false)
	{
		MessageBox(NULL,L"��Ϸ��Դ���أ�",L"��Դ����",NULL);
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
	// ����Ϣѭ��:
	while(msg.message != WM_QUIT)
	{
		if(PeekMessage(&msg,0,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		DWORD now = GetTickCount();
		//������Ⱦʱ��
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
	wcex.lpfnWndProc = WndProc;//�¼���Ӧ����
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance,MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL,IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcex.lpszMenuName = L"MyMenuName";
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance,MAKEINTRESOURCE(IDI_APPLICATION));
	//ע��
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
		//��������ƶ���Ϣ�����ݸ�Game
		{
			WORD x = LOWORD(lParam);
			WORD y = HIWORD(lParam);
			gameEngine->gameMouseMotion(x,y);
		}
		break;
		//����������������Ϣ
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
		//��Ӳ˵���
		AppendMenu(hAddMenu,MF_ENABLED,IDM_qiuhe,L"���");
		AppendMenu(hAddMenu,MF_ENABLED,IDM_fangcha,L"����");
		AppendMenu(hAddMenu,MF_ENABLED,IDM_pingjunzhi,L"ƽ��ֵ");
		AppendMenu(hAddMenu,MF_ENABLED,IDM_junfanggen,L"������");
		//���뵽���˵�
		InsertMenu(hMenu,2,MF_POPUP|MF_BYPOSITION,(UINT)hAddMenu,L"ͳ�Ƽ���(&C)");
		//��Ӧ�ı�˵����йػ�ͼͳ�Ƽ���˵��������
		EnableMenuItem(hMenu,IDM_ADDMENU,MF_GRAYED);
		EnableMenuItem(hMenu,IDM_DELMENU,MF_ENABLED);
		//������ʾ���ڲ˵�
		DrawMenuBar(hWnd);
		break;
	case IDM_DELMENU:
		hMenu = GetMenu(hWnd);
		DeleteMenu(hMenu,2,MF_BYPOSITION);
		//�ı��Ӧ�˵��������
		EnableMenuItem(hMenu,IDM_ADDMENU,MF_ENABLED);
		EnableMenuItem(hMenu,IDM_DELMENU,MF_GRAYED);
		DrawMenuBar(hWnd);
		break;
	case IDM_EXIT:
		SendMessage(hWnd,WM_DESTROY,0,0);//��Ӧ�ó����ͽ�����Ϣ
		break;
	}
}*/