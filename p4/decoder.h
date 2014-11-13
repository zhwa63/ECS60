//Author:Kevin Nguyen and Haowen Angela Zhou
#include "BinaryHeap.h"
#include "HuffNode.h"
#ifndef DECODER_H
#define DECODER_H


#include <iostream>
#include<string>

using namespace std;

class Decoder
{
public:
               Decoder();
	~Decoder();
	void decode(const unsigned char*,const int,unsigned char*, int*);
	
private:
	BinaryHeap<HuffNode*>* theHeap;
};
#endif
