#ifndef _BIT_TOOL_HPP_
#define _BIT_TOOL_HPP_

#define _CRT_SECURE_NO_WARNINGS

#include "llctype.h"
#include <sstream>
#include <iostream>

//64 platform T=long long
//32 platform T=int 
template <typename T>
u64 writeNBitToBuf(T* desBuf, u64 totalBit, T bits, size_t nBit)
{
    
    size_t nT_ = totalBit / (sizeof(T)*8);
    size_t nOverflow = totalBit % (sizeof(T)*8);
    T tmpBits = bits;

    *(desBuf + nT_) |= (bits << nOverflow);

    if(nBit + nOverflow > sizeof(T)*8)
    {       
        *(desBuf + nT_ + 1) = (tmpBits >> (sizeof(T)*8 - nOverflow));
    }
    
    return totalBit + nBit;
}

template <typename T>
T getNBitFromBuf(T* srcBuf, u64 startBit)
{

    size_t nT_ = startBit / (sizeof(T)*8);
    size_t nOverflow = startBit % (sizeof(T)*8);

    T tmpData = 0;
    tmpData = *(srcBuf + nT_) >> nOverflow;

    if (0 != nOverflow)
    {
        tmpData |= (*(srcBuf + nT_ + 1) << (sizeof(T) * 8 - nOverflow));
    }  

    return tmpData;
}

template<typename T>
void mformat(char* buf, const char* strfmt, T first)
{
    sprintf(buf, strfmt, first);
}

template<typename T, typename ... ARGVS>
void mformat(char* buf, const char* strfmt, T first, ARGVS... argvs) 
{    
    sprintf(buf, strfmt, first);
    mformat(buf + strlen(buf), buf, argvs...);
  
}

template<typename T>
void mLog(T strfmt)
{
    std::cout << strfmt << std::endl;
}

template<typename T, typename ... ARGVS>
void mLog(T strfmt, ARGVS... argvs)
{
    //char buf[1024] = { 0 };
    //mformat(buf, strfmt, argvs...);
    //std::cout << buf << std::endl;
    std::cout << strfmt << std::endl;
    mLog(argvs...);
}





#endif
