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


#define FILE_SRC "C:\\Users\\Lerlove\\Desktop\\huffman\\RBD-794.mp4"
#define FILE_COM "C:\\Users\\Lerlove\\Desktop\\huffman\\RBD-794.m"
#define FILE_DES "C:\\Users\\Lerlove\\Desktop\\huffman\\RBD-794.mm"

using namespace std;
using namespace Huffman;

string c_ctr_str = "-c";
string u_ctr_str = "-u";

int parseCmdLine(int argc, char** argvs)
{
    int ret = 0;
    if(argc >= 3)
    {
        if(c_ctr_str == argvs[1])
        {
            //printf("curpath:%s file%s\n", argvs[0], argvs[2]);
            u8* buf = nullptr;
            int len = 0;
            
            fstream fin(argvs[2], ios::binary | ios::in);
            if (fin.is_open())
            {
        
                fin.seekg(0, fstream::end);
                len = (int)fin.tellg();
                mLog("the file len:%d", len);
                fin.seekg(0, fstream::beg);
        
                buf = new u8[len];
                if (!buf)
                {
                    mLog("%s", "the memory  not enough!!!");
                }
                fin.read((char*)buf, len);
                fin.close();
                
                huffmanEncode he(buf, len);
                he.calcuFre();
                mLog("%s", "calcuFre");
                ret = he.createTree();
                mLog("%s ret:%d", "createTree", ret);
                ret = he.createTable();
                mLog("%s ret:%d", "createTable", ret);
                ret = he.writeToFile(argvs[3]);
                mLog("%s ret:%d", "writeToFile", ret);
                delete buf;
            }
        }
        else if(u_ctr_str == argvs[1])
        {
            //printf("curpath:%s file%s %s\n", argvs[0], argvs[2], argvs[3]);
            huffmanDecodeFile(argvs[3], argvs[2]);
        }
        else
        {
            ret = -1;
        }
    }
    else
    {
        ret = -1;
    }
    return ret;;
}

int main(int argc, char** argvs)
{

#if 0
    parseCmdLine(argc, argvs);
#endif
    int ret = 0;
    u8* buf = nullptr;
    int len = 0;

    fstream fin(FILE_SRC, ios::binary | ios::in);
    if (fin.is_open())
    {

        fin.seekg(0, fstream::end);
        len = (int)fin.tellg();
        mLog("the file len:%d", len);
        fin.seekg(0, fstream::beg);

        buf = new u8[len];
        if (!buf)
        {
            mLog("%s", "the memory  not enough!!!");
        }
        fin.read((char*)buf, len);
        fin.close();

        huffmanEncode he(buf, len);
        he.calcuFre();
        mLog("%s", "calcuFre");
        ret = he.createTree();
        mLog("%s ret:%d", "createTree", ret);
        ret = he.createTable();
        mLog("%s ret:%d", "createTable", ret);
        ret = he.writeToFile(FILE_COM);
        mLog("%s ret:%d", "writeToFile", ret);
        delete buf;
    }

    huffmanDecodeFile(FILE_DES, FILE_COM);
    return 0;
}
