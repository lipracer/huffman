#ifndef _HEAP_HPP_

#include <algorithm> 

#define parent(n) ((n-1)/2)
#define lchrd(n) ((2*n)+1)
#define rchrd(n) ((2*n)+2)

using namespace std;

 enum class CmpType : int
{
    less,
};

 bool compare1(int lt, int rt)
 {
     return lt < rt;
 }
 bool compare2(int lt, int rt)
 {
     return lt >= rt;
 }

template<typename T, CmpType cmpType>
class LLHeap
{


    
public:
    bool(*_cmp)(T, T);
    LLHeap(T* src, size_t len):_src(src), _len(len)
    {
        //if (cmpType)
        //{
        //    _cmp = compare2;
        //}
        //else
        //{
        //    _cmp = compare1;
        //}
        _cmp = compare1;
        make_heap();
    }
    
    
    inline void adjust(T* src, size_t loc)
    {
        for(;;)
        {
            size_t nParent = parent(loc);
            if (_cmp(src[loc], src[nParent]))
            {
                swap(src[loc], src[nParent]);
                loc = nParent;
                continue;
            }
            else
            {
                break;
            }
        }
    }

    int make_heap()
    {
        if (_len < 2)
        {
            return 0;
        }
        else
        {
            for (size_t i = 2; i < _len; i++)
            {
                adjust(_src, i);
            }
        }
        return 0;
    }
    // move the maximum or minimum element to last
    void pop_back() 
    {
        int source[10];
        

        swap(_src[0], _src[_len-1]);
        memcpy(source, _src, 40);
        --_len;

        size_t parentloc = 0, targetloc = 0;
        

        for (;;)
        {
            parentloc = targetloc;

            size_t lchrd_ = lchrd(targetloc);
            size_t rchrd_ = rchrd(targetloc);

            if (lchrd_ >= _len || rchrd_ >= _len)
            {
                break;
            }

            if (_cmp(_src[lchrd_], _src[rchrd_]))
            {
                targetloc = lchrd_;
            }
            else
            {
                targetloc = rchrd_;
            }

            if (_cmp(_src[targetloc], _src[parentloc]))
            {
                swap(_src[parentloc], _src[targetloc]);
                memcpy(source, _src, 40);
                
            }
            else
            {
                break;
            }
        }     
        

    }
    void push_back()
    {

    }
private:
    T* _src;
    size_t _len;
};



#endif // !_HEAP_H_

