#pragma once
#include <iostream>

#ifndef __MOTION_CARD__
#define __MOTION_CARD__

#ifndef BDAQCALL
    #ifndef _WIN64
    typedef signed int int32;
    typedef unsigned int uint32;
    #else
    typedef signed long int32;
    typedef unsigned long uint32;
    #endif
#endif


class motion_card
{
public:
    motion_card(){std::cout<<"init"<<std::endl;}
    virtual ~motion_card() { std::cout << "freeing motion card" << std::endl; }

    virtual uint32 ReadInputBit(uint32 bit) = 0;

    virtual void WriteOutput(uint32 bit) = 0;

  //  virtual void 
};



#endif