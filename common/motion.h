#pragma once 
#include <vector>

#include "motion/lesai_dmc1380.h"
#include "motion/motion_card.h"


class motion
{
    private:
		std::vector<motion_card*> m_motion_card;
		int method = 0;
    public :

    motion(int _method = 0){
          method = _method;
    }

	void init() {
		DMC_1380 *dmc_1380card = new DMC_1380(method);

	}
};