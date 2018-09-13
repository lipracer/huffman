
#ifndef HUFFMANENCODE_H
#define HUFFMANENCODE_H

#include "llctype.h"
#include "heap.hpp"

typedef unsigned int CodeVale;

struct TreeNode
{
	size_t freq;
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
        size_t valueLen;
    };

public:
    huffmanEncode(u8 *src, size_t len);
    ~huffmanEncode();
    void calcuFre();
    int createTree();
    int createTable();
    void printTable();

private:
    u8* m_buf;
    size_t m_len;
    TreeNode m_node[NodeCount];
    TreeNode* m_pnode[NodeCount];
    TableElment m_table[256];   

};

#endif
