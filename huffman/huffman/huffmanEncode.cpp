#include "huffmanEncode.h"


huffmanEncode::huffmanEncode()
{

}


huffmanEncode::~huffmanEncode()
{

}

void huffmanEncode::calcuFre(u8 *src, size_t len)
{
	for (size_t i = 0; i < UCHAR_MAX; ++i)
	{
		_aIndex[UCHAR_MAX] = i;
	}

	for (size_t i = 0; i < len; ++i)
	{
		_bTree[*src].chrValue = *src;
		++_bTree[*src++];
	}
}


void huffmanEncode::createTree()
{
	LLHeap<int> mheap(_aIndex, UCHAR_MAX);

	int min1 = mheap.getExtremum();
	int min2 = mheap.getExtremum();

	_bTree[min1].bValue = 0;
	_bTree[min2].bValue = 1;

	TreeNode node;
	node.freq = _bTree[min1].freq + _bTree[min2].freq;

	_bTree.push_back(node);

	_bTree[min1].parent = _bTree.size() - 1;
	_bTree[min2].parent = _bTree.size() - 1;

	mheap.push_back(_bTree.size() - 1);


}