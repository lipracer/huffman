#ifndef _BIT_TOOL_HPP_
#define _BIT_TOOL_HPP_


template <typename T>
size_t writeNBit(T* src, size_t totalBit, T bits, size_t nBit)
{
    
    size_t nInt_ = totalBit / sizeof(T);
    size_t nBit_ = totalBit % sizeof(T);
    
    if(nInt_)
    {
        T* curPos = (src + nInt_);
        T tmpBits = bits;
        tmpBits >> (sizeof(T) - nBit_);
        *(src + nInt_) = *(src + nInt_) | tmpBits;
        if(nBit_ + nBit >= sizeof(T))
        {
            tmpBits = bits;
            *(src + nInt_ + 1) = tmpBits << (sizeof(T) - nBit_);
        }
        
    }
    else
    {
        *(src + nInt_) = bits;
    }
    
    return totalBit + nBit;
}


#endif
