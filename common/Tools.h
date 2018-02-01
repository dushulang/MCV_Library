#pragma once
#include "Time.h"
#include "excv.h"
#include <mutex>
class Tools
{
private:
	Tools() {};
public:
	static Tools* GetIns() {
		static Tools *m_tool = nullptr; if (nullptr == m_tool) { static std::mutex mtx; std::lock_guard<std::mutex> lck(mtx); m_tool = new Tools(); }
		return m_tool;
	}
	//���ܣ�����������Сʱ�������Ӻͺ���
	char *Get_Time_zzz()
	{
		return _Timer::GetIns()->Get_Time_zzz();
	}

	//�������õ���ģʽ
	excv Excv;
};