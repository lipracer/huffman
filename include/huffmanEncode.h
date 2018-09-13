
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
        CodeVale vale;
        u8 valueLen;
    };

private:
    TreeNode m_node[NodeCount];
    TreeNode* m_pnode[NodeCount];

    TableElment m_table[256];


public:

	huffmanEncode();
	~huffmanEncode();
	void calcuFre(u8 *src, u8 len);
	int createTree();
	int createTable();
};

#endif
