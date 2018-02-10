#pragma once
#include <iostream>

#ifdef QT_VERSION
#include <QDateTime>
#endif
//_Extend
class _Timer
{
private:
	_Timer() {}
public:
	static _Timer* GetIns() { static _Timer _T; return &_T; }

	//accurcy to zzz
	char * Get_Time_zzz()
	{
#ifdef QT_VERSION
		return QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss-zzz");
		std::cout << "qt" << std::endl;
#else
	#ifdef __AFX_H__ 
			SYSTEMTIME st;
			CString strTime;
			GetLocalTime(&st);
			strTime.Format(L"%4d-%d-%d-%d-%d-%d-%d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
			//std::cout << (char*)(LPCSTR)(CStringA)strTime<< std::endl;
			return (char*)(LPCSTR)(CStringA)strTime;
	#else
		#error unknown library
	#endif
#endif
	}

};