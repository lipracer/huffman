
#ifndef HUFFMANENCODE_H
#define HUFFMANENCODE_H

typedef int sizeType;
class huffmanEncode
{
	enum valueEnum
	{
		UCHAR_MAX = 255,
	};
private:
	sizeType _afrequency[UCHAR_MAX];
public:
	huffmanEncode();
	~huffmanEncode();
	void calcuFre(unsigned char *src, sizeType len);
};

#endif