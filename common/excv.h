#pragma once
#include <iostream>
#include <vector>
#include <mutex>
#include "Time.h"
#include "exstring.h"
#include "cv_module\letter_recog.h"
#include "cv_module\caffe.h"
/*
���ĵ���д��һ����̬��
excv��˼��extend computer vision �ǽ�����opencv֮�ϵ�

*/

#ifndef _WIN64
#error not support win32, win64 is OK
#endif

//��������������������
// /D "__USE_OPENCV__"
#define __USE_OPENCV__
#ifdef __USE_OPENCV__
#include "opencv2/opencv.hpp"
#if _MSC_VER<1900
#error MSC_VER is too low
#else
#pragma comment(lib,"../../third_party/opencv3.4.0/x64/vc14/lib/opencv_world340.lib")
//#pragma comment(lib,"../opencv3.4.0/x64/vc15/lib/opencv_world340.lib")
#endif
#endif


#ifndef __USE_OPENCV__
#error need opencv
#else

#ifndef MAX_INT
#define MAX_INT    (((unsigned int)(-1))>>1)
#endif

#ifndef MIN_INT
#define MIN_INT    (MAX_INT+1)    
#endif

//����Ҫ����
class excv
{
private:
	std::string m_name;

	void Init() {
		std::cout << "start init" << std::endl;
	}
public:
	excv(char * name) :m_name(name) {};
	excv() { Init(); };
	~excv() { Init(); };


//	//����ģʽ
//	static excv* GetIns() { static std::mutex mtx; std::lock_guard<std::mutex> lck(mtx); static excv *ec = nullptr; if (nullptr == ec) { ec = new excv(); }return ec; }
	//�����������
	//��Ҫָ��Ż�
	float distance(cv::Point2f &a, cv::Point2f &b)
	{
		return euclidean_distance(a, b);
	}

	inline float euclidean_distance(cv::Point2f &a, cv::Point2f &b)
	{
		return std::sqrtf((b.x - a.x)*(b.x - a.x) + (b.y - a.y)*(b.y - a.y));
	}

	float mahalanobis_distance(cv::Point2f &a, cv::Point2f &b, int n = 2)
	{
		return 0.0;
	}

	//�ҵ����������
	inline int find_max_contours_id(std::vector<std::vector<cv::Point>> &contours)
	{
		try {
			size_t size = contours.at(0).size();
			int max_id = 0; //-1  is invalid
			for (size_t i = 0; i < contours.size(); i++){
				if (size < contours[i].size()){
					size = contours[i].size();
					max_id = i;
				}
			}
			return max_id;
		}
		catch (std::out_of_range e)
		{
			std::cout << e.what() << std::endl;
			return -1;
		}
	}



	//����ʱ������¼ͼƬ
	void cv_write_image(const cv::Mat & m, char* path = "")
	{	if (m.empty()) return;
		char fileName[_MAX_PATH] = { 0 };
		if (0 == strlen(path))
			sprintf_s(fileName, "%s.bmp", _Timer::GetIns()->Get_Time_zzz());
		else
			sprintf_s(fileName, "%s/%s.bmp", path, _Timer::GetIns()->Get_Time_zzz());
		cv::imwrite(fileName, m);
	}

	//��ȡ
	void get_mask_image(const cv::Mat& src, cv::Mat& dst, std::vector<std::vector<cv::Point>>& contours, int ID)
	{
		using namespace cv;
		if (src.empty()) return;
		Mat Mask(src.size(), CV_8U, Scalar(0));
		const int widthStep = static_cast<int>(src.step);
		const int height = static_cast<int>(src.rows);
		uchar *sdata = src.data;
		uchar *ddata = Mask.data;
		drawContours(Mask, contours, ID/*��õ��������*/, Scalar(255), CV_FILLED/*2*/);
#pragma omp parallel
		for (int h = 0; h < height; h++)
		{
			for (int w = 0; w < widthStep; w++)
			{
				ddata[w] &= sdata[w];
			}
			sdata += widthStep;
			ddata += widthStep;
		}
		dst = Mask.clone();
	}

	//��ϣ���޷�ֱ�ӹ�ϣcv::Point������ת���ַ���
	static std::string Point2str(const cv::Point& pt)
	{
#ifdef __AFX_H__1
#else
		std::ostringstream ostr;
		ostr<< pt.x << "," << pt.y;
		std::string str(ostr.str());
		ostr.clear();
		return str;
#endif
	}

	static cv::Point str2Point(std::string &str)
	{
		std::vector<std::string> pts = tl::exstring::split(str,",");
		try{
			return cv::Point(std::atoi(pts.at(0).c_str()), std::atoi(pts.at(1).c_str()));
		}
		catch (std::out_of_range e)
		{
			std::cout << "str2Point split error" << std::endl;
		}
	}
};
#endif