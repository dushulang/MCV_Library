#pragma once
#include <iostream>
//_Extend
class _Timer
{
private:
	_Timer() {}
public:
	static _Timer* GetIns() { static _Timer _T; return &_T; }
	//���ܣ�����������Сʱ�������Ӻͺ���
	char * Get_Time_zzz()
	{
#ifdef QT_VERSION
		std::cout << "qt" << std::endl;
		return Get_Time_zzz().toLatin1().data());
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