
#ifndef HUFFMANENCODE_H
#define HUFFMANENCODE_H

#include "llctype.h"

class huffmanEncode
{
	enum valueEnum
	{
		UCHAR_MAX = 255,
	};

private:

    struct TreeNode
    {
        TreeNode* parent;
        int bValue;
    };

    struct Freq
    {
    	size_t freq;
    	u8 charValue;
    };
	Freq _afrequency[UCHAR_MAX];
public:
	huffmanEncode();
	~huffmanEncode();
	void calcuFre(u8 *src, size_t len);
};

#endif