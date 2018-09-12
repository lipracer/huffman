//test heap
#ifndef _TEST_HEAP_HPP_
#define _TEST_HEAP_HPP_


#define ALENGTH 1000
#define mrand(x) (rand()%(x))

#include "heap.hpp"
#include "huffmanEncode.h"
#include "bit_tool.hpp"

struct cmp
{
    bool operator()(int a, int b)
    {
        return a >= b;
    }
};

int* getDisorderArray()
{
    int* ret = new int[ALENGTH];
    for(int i = 0; i < ALENGTH; ++i)
    {
        ret[i] = i;
    }
    
    int lastPos = ALENGTH - 1;
    for (; lastPos>0; ) {
        swap(ret[lastPos], ret[mrand(lastPos+1)]);
        --lastPos;
    }
    return ret;
}

int test_heap()
{
    int* src = getDisorderArray();
    for(int i = 0; i < ALENGTH; i++)
    {
        cout << src[i] << " ";
    }
    cout << endl;
    LLHeap<int, cmp> heap(src, ALENGTH);
    
    for(int i = 0; i < ALENGTH - 1; i++)
    {
        heap.pop_back();
    }
    
    for(int i = 0; i < ALENGTH; i++)
    {
        cout << src[i] << " ";
    }
    
    delete src;
    return 0;

}

#endif
