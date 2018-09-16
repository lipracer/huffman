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
#include <fstream>
#include <bitset>

#include "test_heap.hpp"
#include "test_huffman.hpp"
#include "huffmanEncode.h"


#define FILE_SRC "C:\\Users\\Lerlove\\Desktop\\huffman\\test.pdf"
#define FILE_COM "C:\\Users\\Lerlove\\Desktop\\huffman\\test_.pdf"
#define FILE_DES "C:\\Users\\Lerlove\\Desktop\\huffman\\test__.pdf"

using namespace std;
using namespace Huffman;

int main()
{
    // insert code here...
    //test_heap();

    u8* buf = nullptr;
    int len = 0;

    //getTestBuf(buf, len);
    

#if true
    fstream fin(FILE_SRC, ios::binary | ios::in);

    if (fin.is_open()) 
    {
 
        fin.seekg(0, ios::_Seekend);
        len = fin.tellg();
        fin.seekg(0, ios::_Seekbeg);

        buf = new u8[len];
        fin.read((char*)buf, len);
        fin.close();
    }
#endif


        //huffmanEncode he(buf, len);
        //he.calcuFre();
        //he.createTree();
        //he.createTable();
        //he.writeToFile(FILE_COM);
        huffmanDecodeFile(FILE_DES, FILE_COM);

        delete buf;
    system("pause");
    return 0;
}
