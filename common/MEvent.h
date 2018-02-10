#include <mutex>
#ifndef ___EVENT___MSERIALS___
#define ___EVENT___MSERIALS___


class MEvent
{
private:
	std::mutex mtx;
#ifdef __AFX_H__
    CEvent evt;
    int state;
#endif
public:

#ifdef __AFX_H__
	MEvent(){
      evt.ResetEvent();
      state = 0;}

	int SetEvent() { 
		std::lock_guard<std::mutex> lck(mtx);
		BOOL success = evt.SetEvent(); 
		if (state || success)
		{
			return (state = 1);
		}
		return state;
	}

	int ResetEvent() {
		std::lock_guard<std::mutex> lck(mtx);
		BOOL success = evt.ResetEvent();
		if (state && !success)
		{
			return (state = 1);
		}
		return (state = 0);
	}

	int State(){return state;}

	const CEvent & get() {
		return evt;
	}

    #else
  MEvent(){};
  #endif
};



#endif