// KeyBoard.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "KeyBoard.h"

#define MAX_LOADSTRING 100
#define _CRT_SECURE_NO_WARNNINGS

// ȫ�ֱ���:
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������

// �˴���ģ���а����ĺ�����ǰ������:
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

 	// TODO: �ڴ˷��ô��롣
	MSG msg;
	HACCEL hAccelTable;

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_KEYBOARD, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_KEYBOARD));

	// ����Ϣѭ��:
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
//  ����: MyRegisterClass()
//
//  Ŀ��: ע�ᴰ���ࡣ
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
//   ����: InitInstance(HINSTANCE, int)
//
//   Ŀ��: ����ʵ�����������������
//
//   ע��:
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

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
//  ����: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��: ���������ڵ���Ϣ��
//
//  WM_COMMAND	- ����Ӧ�ó���˵�
//  WM_PAINT	- ����������
//  WM_DESTROY	- �����˳���Ϣ������
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
			//��ȡ������Ϣ
			GetTextMetrics(hdc,&tm);
			//����ÿ�еĸ߶Ⱥ��м��
			nLnHeight = tm.tmHeight + tm.tmExternalLeading;
			//�����ַ���ƽ�����
			nCharWidth = tm.tmAveCharWidth;
			//�������ַ�
			CreateCaret(hWnd,NULL,nCharWidth/10,tm.tmHeight);
			//��ʾ���ַ�
			ShowCaret(hWnd);

			ReleaseDC(hWnd,hdc);
		}
		break;
	case WM_CHAR://��ϵͳ�ַ��������Ĵ���
		{
			if(wParam == VK_BACK)
			{
				if(nX == 0)//����Ѿ���һ�����ֵĿ�ͷ
				{
					if(nNumLine > 0)
					{
						nY--;
						nX = nArrayPos[nY];
					}
					else
					{
						nX = nY = nNumLine = nArrayPos[0] = 0;
						MessageBox(hWnd,L"�ѵ��ļ�ͷ������ɾ���ַ�",NULL,MB_OK);
					}
				}
				else
				{
					nArrayPos[nY] -= 1;
					//�������ַ����µ���
					for(int i=nX;i<nArrayPos[nY];i++)
						cCharInfo[nY][i] = cCharInfo[nY][i - 1];
					nX--;
				}
				//����ˢ���û�����
				InvalidateRect(hWnd,NULL,TRUE);
				break;
			}
			else if(wParam == VK_RETURN)
			{
				nNumLine++;
				if(nNumLine >= MAXLINE)
				{
					nY = nNumLine;
					MessageBox(hWnd,L"�ѳ����������",NULL,MB_OK);
					break;
				}
				nArrayPos[nY] = nX;
				//�������ϵ���
				for(int i=nNumLine;i > nY + 1;i--)
				{
					
					wcscpy_s(cCharInfo[i],cCharInfo[i-1]);
					nArrayPos[i] = nArrayPos[i-1];
				}
				wcscpy_s(cCharInfo[nY + 1],&cCharInfo[nY][nX]);
				//����ǰ�е����ಿ�ָ��Ƶ���һ��
				cCharInfo[nY][nX] ='\0';
				nY++;
				nX = 0;
				nArrayPos[nY] = _tcslen(cCharInfo[nY]);
			}
			else//�����ַ�
			{
				//�����ǰ�ַ�û�г������ƣ��Ͳ������ַ�
				if(nArrayPos[nY] < MAXNUMCHAR - 1)
				{
					cCharInfo[nY][nArrayPos[nY] + 1] = '\0';
					for(int x = nArrayPos[nY];x>nX;x = x -1)
						cCharInfo[nY][x] = cCharInfo[nY][x-1];
					cCharInfo[nY][nX] = (TCHAR)wParam;
					nArrayPos[nY] += 1;
					nX++;
				}//����
				else
				{
					nNumLine++;
					if(nNumLine > MAXLINE)
					{
						nY = nNumLine;
						MessageBox(hWnd,L"���������",NULL,MB_OK);
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
					MessageBox(hWnd,L"���е�ǰλ��Ϊ�գ�û���ַ���ɾ����",NULL,MB_OK);
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
		// �����˵�ѡ��:
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
		// TODO: �ڴ���������ͼ����...
		for(int i=0;i<=nNumLine;i++)
			TextOut(hdc,0,nLnHeight*i,cCharInfo[i],nArrayPos[i]);
		SIZE size;
		GetTextExtentPoint(hdc,cCharInfo[nY],nX,&size);
		//���ַ�������
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

// �����ڡ������Ϣ�������
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
