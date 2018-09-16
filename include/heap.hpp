#ifndef _HEAP_HPP_
#define _HEAP_HPP_

#include <algorithm>
#include <iostream>

#define parent(n) ((n-1)/2)
#define lchrd(n) ((2*n)+1)
#define rchrd(n) ((2*n)+2)

using namespace std;


template<typename T, typename CMP>
class LLHeap
{
    
public:
    CMP _cmp;
    LLHeap(T* src, size_t len):_src(src), _len(len)
    {
        make_heap();
    }
    
    
    inline void adjust(T* src, size_t loc)
    {
        int curPos = loc;
        int nParent = parent(loc);
        for(;;)
        {
            if (_cmp(src[curPos], src[nParent]))
            {
                swap(src[curPos], src[nParent]);
                curPos = nParent;
                nParent = parent(curPos);
            
                if(nParent < 0)//nParent is int so can if by less 0
                {
                    break;
                }
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
            for (size_t i = 1; i < _len; i++)
            {
                adjust(_src, i);
            }
        }
        return 0;
    }
    // move the maximum or minimum element to last
    void pop_back() 
    {
        if(1 == _len)
        {
            --_len;
            return;
        }        

        swap(_src[0], _src[_len-1]);
        --_len;

        size_t parentloc = 0, targetloc = 0;
        

        for (;;)
        {
            parentloc = targetloc;

            size_t lchrd_ = lchrd(targetloc);
            size_t rchrd_ = rchrd(targetloc);

            if (lchrd_ < _len && rchrd_ < _len)
            {
                if (_cmp(_src[lchrd_], _src[rchrd_]))
                {
                    targetloc = lchrd_;
                }
                else
                {
                    targetloc = rchrd_;
                }
            }
            else if(rchrd_ >= _len && lchrd_ < _len)
            {
                targetloc = lchrd_;
            }
            else if(rchrd_ >= _len)
            {
                break;
            }

            if (_cmp(_src[targetloc], _src[parentloc]))
            {
                swap(_src[parentloc], _src[targetloc]);
                
            }
            else
            {
                break;
            }
        }     
    }
    void push_back(T& element)
    {
        _src[_len] = element;
        adjust(_src, _len);
        ++_len;
    }

    size_t size()
    {
        return _len;
    }

    T getExtremum()
    {
        if(0 == _len)
        {
            throw 0;
        }
        pop_back();
        return _src[_len];
    }
    void debugOut()
    {
        for (int i = 0; i < _len; ++i)
        {
            cout << _src[i] << " ";
        }
        cout << endl;
    }
private:
    T* _src;
    size_t _len;
};



#endif // !_HEAP_H_
