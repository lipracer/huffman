//
//  main.cpp
//  test_huffman
//
//  Created by multimedia on 2018/9/11.
//  Copyright © 2018年 ___multiMedia___. All rights reserved.
//

#include <random>
#include <iostream>
#include <memory>
#include <sstream>
#include "heap.hpp"
#include "huffmanEncode.h"

#define ALENGTH 1000
#define mrand(x) (rand()%(x))

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


int main(int argc, const char * argv[]) {
    // insert code here...
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

    huffmanEncode he;

    return 0;
}
