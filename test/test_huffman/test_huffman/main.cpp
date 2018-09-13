//
//  main.cpp
//  test_huffman
//
//  Created by multimedia on 2018/9/11.
//  Copyright © 2018年 ___multiMedia___. All rights reserved.
//
#include <cstdio>
#include <cstdlib>

#include <random>
#include <iostream>
#include <memory>
#include <sstream>

#include "test_heap.hpp"
#include "test_huffman.hpp"
#include "huffmanEncode.h"


int main()
{
    // insert code here...
    //test_heap();

    u8* buf = nullptr;
    int len = 0;

    //getTestBuf(buf, len);

    FILE *pf = nullptr;

#ifndef _WINDOWS
    errno_t err = fopen_s(&pf, "E:\\myProject\\huffman\\C++Design.pdf", "rb+");
#else
    pf = fopen("E:\\myProject\\huffman\\C++Design.pdf", "rb+");
#endif // !_WINDOWS


    if (pf) 
    {
        fseek(pf, 0, SEEK_END);
        len = ftell(pf);
        fseek(pf, 0, SEEK_SET);

        buf = new u8[len];
        fread(buf, len, 1, pf);
        fclose(pf);


        huffmanEncode he(buf, len);
        he.calcuFre();
        he.createTree();
        he.createTable();
        he.printTable();

        delete buf;
    }

    system("pause");
    return 0;
}
