#include "MyUtility.h"
std::string MyUtility::getCurrentTime()
{
	return "";
}
std::string MyUtility::gbk_to_utf8(const std::string&text)
{
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	//采用Lambda表达式,将string转换成wstring
	std::wstring tes = [=]() {
		setlocale(LC_ALL, "chs"); 
		const char* _Source = text.c_str();
		size_t _Dsize = text.size() + 1;
		wchar_t *_Dest = new wchar_t[_Dsize];
		wmemset(_Dest, 0, _Dsize);
		mbstowcs(_Dest,_Source,_Dsize);
		std::wstring result = _Dest;
		delete []_Dest;
		setlocale(LC_ALL, "C");
		return result;
	}();

	int asciSize = WideCharToMultiByte(CP_UTF8,0,tes.c_str(),tes.size(),NULL,0,NULL,NULL);
	if (asciSize == ERROR_NO_UNICODE_TRANSLATION || asciSize == 0)	
	{
		return std::string();
	}

	char *resultString = new char[asciSize];
	int conveResult = WideCharToMultiByte(CP_UTF8,0,tes.c_str(),tes.size(),resultString,asciSize,NULL,NULL);
	if (conveResult != asciSize)
	{
		return std::string();
	}
	std::string buffer = "";
	buffer.append(resultString,asciSize);

	delete[] resultString;
	return buffer;

#else
	return text;
#endif
}
std::string MyUtility::getUTF8Char(const std::string&key)
{
	return "";
}
