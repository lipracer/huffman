#ifndef _HEAP_HPP_

#define parent(n) ((n-1)/2)
#define lchrd(n) ((2*n)+1)
#define rchrd(n) ((2*n)+2)

enum  CmpType : int
{
    less,
};

template<typename T, CmpType cmpType>
class LLHeap
{

    bool compare1(T lt, T rt) 
    {
        return lt < rt;
    }
    bool compare2(T lt, T rt)
    {
        return lt >= rt;
    }
    
public:
    LLHeap(T* src, size_t len):_src(src), _len(len)
    {
        make_heap();
    }
    int(*_cmp)(T, T);
    LLHeap() 
    {
        if (cmpType)
        {
            _cmp = compare2;
        }
        else 
        {
            _cmp = compare1;
        }
    }
    inline int adjust(T* src, size_t loc)
    {
        while (true)
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

    int pop_back() 
    {

    }
private:
    T* _src;
    size_t _len;
};



#endif // !_HEAP_H_

