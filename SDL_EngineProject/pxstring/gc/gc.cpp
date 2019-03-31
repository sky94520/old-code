#include<iostream>
#include<string>
#include<Windows.h>

bool CopyToClipBoard(std::wstring &s)
{
	if (FAILED(OpenClipboard(NULL)))return false;
	HGLOBAL hClip;
	EmptyClipboard();
	hClip = GlobalAlloc(GMEM_MOVEABLE, (s.length() + 1) * sizeof(wchar_t));
	wchar_t *pBuffer = (wchar_t*)GlobalLock(hClip);
	lstrcpy(pBuffer, s.c_str());
	GlobalUnlock(hClip);
	SetClipboardData(CF_UNICODETEXT, hClip);
	CloseClipboard();
	return true;
}
int wmain()
{
	using namespace std;
	locale::global(locale("zh-CN"));
	wcout.imbue(locale("zh-CN"));
	wchar_t fchar;
	char mem[8];
	wchar_t str[8][8], buf[8];
	wstring outstr;
	wcout << L"Enter ForeChar:";
	wcin >> fchar;
	getwchar();
	
	bool run = true;
	while (run)
	{
		wcout << L"Enter:\n";
		memset(mem, 0, 8);
		for (int j = 0; j < 8; j++)
		{
			for (int i = 0; i < 8; i++)
			{
				wcin >> str[j][i];
				if (str[j][i] == L'q')
				{
					run = false;
					break;
				}
			}
			if (!run)break;
		}
		if (!run)break;
		wcout << "Your Input is:\n";
		for (int j = 0; j < 8; j++)
		{
			for (int i = 0; i < 8; i++)
				wcout << str[j][i];
			wcout << endl;
		}
		for (int j = 0; j < 8; j++)
			for (int i = 0; i < 8; i++)
			{
				mem[j] <<= 1;
				if (str[j][i] == fchar)mem[j] += 1;
			}
		outstr.clear();
		for (int i = 0; i < 8; i++)
		{
			wsprintf(buf, L"\'\\x%02X\',", mem[i] & 0xFF);
			outstr += buf;
		}
		CopyToClipBoard(outstr);
		wcout << outstr << endl;
	}
}