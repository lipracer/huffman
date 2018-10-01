#ifndef _BIT_TOOL_HPP_
#define _BIT_TOOL_HPP_
#include "llctype.h"

//64 platform T=long long
//32 platform T=int
template <typename T>
void writeNBitToBuf(T* desBuf, u64 nOverflow, T bits, size_t nBit)
{    

    *(desBuf) |= (bits << nOverflow);

    if(nBit + nOverflow > sizeof(T)*8)
    {    
        T tmpBits = bits;
        *(++desBuf) = (tmpBits >> (sizeof(T)*8 - nOverflow));
    }
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

#endif
