#ifndef __ErrorInfo_H__
#define __ErrorInfo_H__

#include<fstream>
#include<string>

class ErrorInfo  
{
private:
     //保存log日志
     std::ofstream m_fileLog;
  static ErrorInfo *s_pInstance;
    ErrorInfo()
    {
        m_fileLog.open("log",std::ios::out);
    }

public:
     ~ErrorInfo(){}
  static ErrorInfo *Instance()
  {
	if (s_pInstance == NULL)
	    s_pInstance = new ErrorInfo();
	return s_pInstance;
  }
  void log(std::string str)
  {
	m_fileLog.open("log",std::ios::app);
	m_fileLog<<str<<std::endl;
	m_fileLog.close();
  }
  void log(float num)
  {
	m_fileLog.open("log",std::ios::app);
	m_fileLog<<num<<std::endl;
	m_fileLog.close();
   }
};
#endif
ErrorInfo*ErrorInfo::s_pInstance = NULL;