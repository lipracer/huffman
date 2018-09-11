
#ifndef HUFFMANENCODE_H
#define HUFFMANENCODE_H

#include "llctype.h"
#include "heap.hpp"

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
    bool operator()(T& lt, T& rt)
    {
        return lt.freq < rt.freq;
    }
};

template<typename T>
struct compare2
{
    bool operator()(T& lt, T& rt)
    {
        return lt.freq >= rt.freq;
    }
};

class huffmanEncode
{
	enum valueEnum
	{
		UCHAR_MAX = 255,
        NodeCount = (256+1)*256/2
	};

private:
    TreeNode m_node[NodeCount];
    TreeNode* m_pnode[NodeCount];


public:

	huffmanEncode();
	~huffmanEncode();
	void calcuFre(u8 *src, size_t len);
	void createTree();
	void createTable();
};

#endif
