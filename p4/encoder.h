//Author: Kevin Nguyen and Angela Haowen Zhou
#include "BinaryHeap.h"
#include "HuffNode.h"
#ifndef ENCODER_H
#define ENCODER_H

class Encoder
{
public:
	Encoder();
	~Encoder();
	void encode(const unsigned char*, const int, unsigned char*, int*);
	void printCode(HuffNode*,unsigned int, unsigned int,int);

private:

	BinaryHeap<HuffNode*>* theHeap;
	unsigned int coded[256][8];
	unsigned int frequency[256];
	int lengths[256];
};
#endif
