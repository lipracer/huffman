
#ifndef HUFFMANENCODE_H
#define HUFFMANENCODE_H

#include "llctype.h"
#include "heap.hpp"

typedef unsigned int CodeVale;

struct TreeNode
{
	u32 freq;
    TreeNode* parent;
    int bValue;
	u8 charValue;
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
	enum valueEnum
	{
		MUCHAR_MAX = 255,
        NodeCount = (256+1)*256/2
	};

    struct TableElment 
    {
        CodeVale value;
        u32 valueLen;
    };

public:
    huffmanEncode(u8 *src, u32 len);
    ~huffmanEncode();
    void calcuFre();
    int createTree();
    int createTable();
    void printTable();

private:
    u8* m_buf;
    u32 m_len;
    TreeNode m_node[NodeCount];
    TreeNode* m_pnode[NodeCount];
    TableElment m_table[256];   

};

#endif
