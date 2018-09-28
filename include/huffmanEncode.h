
#ifndef HUFFMANENCODE_H
#define HUFFMANENCODE_H

#include "llctype.h"
#include "heap.hpp"
#include "big_buf.hpp"
#include <string>

namespace Huffman 
{
    typedef unsigned int CodeVale;

    struct TreeNode
    {
        size_t freq;
        u32 bValue;
        u8 charValue;
        TreeNode* parent;
    };

    template<typename T>
    struct compare1
    {
        bool operator()(T lt, T rt)
        {
            return lt->freq < rt->freq;
        }
    };

    template<typename T>
    struct compare2
    {
        bool operator()(T lt, T rt)
        {
            return lt->freq >= rt->freq;
        }
    };

    class huffmanEncode
    {
    public:
        enum valueEnum
        {
            MUCHAR_MAX = 255,
            NodeCount = (256 + 1) * 256 / 2
        };

        struct TableElment
        {
            CodeVale value;
            size_t valueLen;
        };

    public:
        huffmanEncode(string filename);
        huffmanEncode(u8 *src, size_t len);
        ~huffmanEncode();
        void calcuFre();
        int createTree();
        int createTable();
        u64 writeCcompressData(u8* desBuf);
        int writeToFile(string filename);

        void printTable();

    private:
        u8 * m_buf;
        u64 m_len;
        TreeNode m_node[NodeCount];
        TreeNode* m_pnode[NodeCount];

    public:
        TableElment m_table[256];

    };

    
    //struct fileStruct
    //{
    //    char head[8];
    //    u64 originFileLen;
    //    u64 nBits;
    //    huffmanEncode::TableElment hf_table[256];
    //};

    int huffmanDecode(CodeVale* srcBuf, u64 totalBit, huffmanEncode::TableElment* huffmanTB, u8* destBuf);

    int huffmanDecodeFile(string destfilename, string srcfilename);
}
#endif
