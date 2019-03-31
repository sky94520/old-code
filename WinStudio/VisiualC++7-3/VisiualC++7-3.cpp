// VisiualC++7-3.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "VisiualC++7-3.h"

#define MAX_LOADSTRING 100

// ȫ�ֱ���:
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������
HWND hdlg;
TCHAR str[200];

// �˴���ģ���а����ĺ�����ǰ������:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK ModalDlgProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam);
BOOL CALLBACK ModalessDlgProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam);



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
	LoadString(hInstance, IDC_VISIUALC73, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_VISIUALC73));

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_VISIUALC73));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_VISIUALC73);
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
   //����˵���
   HMENU menu = LoadMenu(hInstance,L"MyMenu");

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, menu, hInstance, NULL);

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
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// �����˵�ѡ��:
		switch (wmId)
		{
		case IDM_OPEN:
			MessageBox(hWnd,L"�ļ��Ѿ���",L"�ļ���",MB_OK);
			break;
		case IDM_SAVE:
			MessageBox(hWnd,L"�ļ�����ɹ�",L"�ļ�����",MB_OK);
			break;
		case IDM_EXIT:
			SendMessage(hWnd,WM_DESTROY,0,0);
			break;
		case IDM_MODAL:
			DialogBox(hInst,MAKEINTRESOURCE(IDD_DIALOG1),hWnd,(DLGPROC)ModalDlgProc);
			break;
		case IDM_MODALLESS:
			hdlg = CreateDialog(hInst,MAKEINTRESOURCE(IDD_DIALOG1),hWnd,(DLGPROC)ModalessDlgProc);
			break;
		case IDM_HELP:
			
			break;
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: �ڴ���������ͼ����...
		TextOut(hdc,0,0,str,wcslen(str));
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
BOOL CALLBACK ModalDlgProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	TCHAR mystr[200];
	switch(message)
	{
	case WM_INITDIALOG:
		SetDlgItemText(hdlg,IDC_TITLE,L"ģʽ�Ի���");
		return 1;
		break;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDOK:
			GetDlgItemText(hdlg,IDC_EDIT1,mystr,200);
			wcscpy_s(str,L"����ģʽ�Ի������Ϣ:");
			wcscat_s(str,mystr);
			InvalidateRect(GetParent(hdlg),NULL,true);
			EndDialog(hdlg,0);
			return 1;
			break;
		case IDCANCEL:
			SetDlgItemText(hdlg,IDC_EDIT1,L"");
			break;
		}
		break;
	case WM_CLOSE:
		EndDialog(hdlg,0);
		break;
	}
}
BOOL CALLBACK ModalessDlgProc(HWND hdlg,UINT message,WPARAM wParam,LPARAM lParam)
{
	TCHAR mystr[200];
	switch(message)
	{
	case WM_INITDIALOG:
		SetDlgItemText(hdlg,IDC_TITLE,L"��ģʽ�Ի���ʾ��");
		return 1;
		break;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDOK:
			GetDlgItemText(hdlg,IDC_EDIT1,mystr,200);
			wcscpy_s(str,L"���Ƿ�ģʽ�Ի����������Ϣ:");
			wcscat_s(str,mystr);
			InvalidateRect(GetParent(hdlg),NULL,true);
			DestroyWindow(hdlg);
			return 1;
			break;
		case IDCANCEL:
			SetDlgItemText(hdlg,IDC_EDIT1,L"");
			DestroyWindow(hdlg);
			return 1;
			break;
		}
		break;
	case WM_CLOSE:
		DestroyWindow(hdlg);
		return 1;
	break;
	}
}