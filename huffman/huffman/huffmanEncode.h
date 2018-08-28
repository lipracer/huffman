
#ifndef HUFFMANENCODE_H
#define HUFFMANENCODE_H

#include "llctype.h"
#include "heap.hpp"

class huffmanEncode
{
	enum valueEnum
	{
		UCHAR_MAX = 255,
	};

private:

    struct TreeNode
    {
    	size_t freq;
        TreeNode* parent;
        int bValue;
    	u8 charValue;
    };

    std::vector<TreeNode> _bTree(UCHAR_MAX);
    int _aIndex[UCHAR_MAX];

public:

	huffmanEncode();
	~huffmanEncode();
	void calcuFre(u8 *src, size_t len);
	void createTree();
	void createTable();
};

#endif