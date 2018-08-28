
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

class huffmanEncode
{
	enum valueEnum
	{
		UCHAR_MAX = 255,
	};

private:



    std::vector<TreeNode> _bTree(UCHAR_MAX);
    TreeNode* _apNode[UCHAR_MAX];//the source freq index array will sort

    u32 _htable[UCHAR_MAX];//huffman encode table

public:

	huffmanEncode();
	~huffmanEncode();
	void calcuFre(u8 *src, size_t len);
	void createTree();
	void createTable();
};

#endif