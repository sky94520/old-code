#include<fstream>
#define FILE_NAME "log"

#pragma once
class ErrorInfo
{
	private:
	std::fstream logFile;
	private:
	ErrorInfo();
	public:
	static ErrorInfo * Instance();
	~ErrorInfo();
	void log(const char*log);
};
typedef ErrorInfo TheErrorInfo;

ErrorInfo*ErrorInfo::Instance()
{
	static ErrorInfo s_pInstance;
	
	return &s_pInstance;
}
ErrorInfo::ErrorInfo()
{
	logFile.open(FILE_NAME,std::ios::out);
	logFile.close();
}
ErrorInfo::~ErrorInfo()
{
}
void ErrorInfo::log(const char*log)
{
	logFile.open(FILE_NAME,std::ios::app);
	logFile<<log<<"\n";
	logFile.close();
}