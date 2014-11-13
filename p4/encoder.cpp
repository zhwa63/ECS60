//Author: Kevin Nguyen and Haowen Angela Zhou

#include "encoder.h"
// make node class with char, frequency. two constructors one for leaves one for node. Have a boolean to keep leaves



Encoder::Encoder()
{
	theHeap= new BinaryHeap<HuffNode*>(256);// the heap to initally hold the frequencies
	
	for( int Ar=0;Ar<256;Ar++)
	{
		frequency[Ar]=0;
		lengths[Ar]=0;
		/*	coded[Ar][0]=0;
		coded[Ar][1]=0;
		coded[Ar][2]=0;
		coded[Ar][3]=0;
		coded[Ar][4]=0;
		coded[Ar][5]=0;
		coded[Ar][6]=0;
		coded[Ar][7]=0;
		*/
	}//end initializing of frequency
	
}//Encoder()

Encoder::~Encoder()
{
  delete theHeap;
	
}// ~Encoder()

void Encoder::printCode(HuffNode* x,unsigned int code, unsigned int mask,int length)
{
	if (x->isLeaf())
	{
		int index = (int)x->letter;
		lengths[index]=length;
		coded[index][0]|=code;
		coded[index][1]|=(code>>1);
		coded[index][2]|=(code>>2);
		coded[index][3]|=(code>>3);
		coded[index][4]|=(code>>4);
		coded[index][5]|=(code>>5);
		coded[index][6]|=(code>>6);
		coded[index][7]|=(code>>7);
	}
	else
	{
		printCode(x->left,code,mask>>1,length+1);
		printCode(x->right,code|mask,mask>>1,length+1);
	}//end not leaf
	
}//end printCode

void Encoder::encode(const unsigned char *message, const int size, unsigned char *encodedMessage, int *encodedSize)
{
	*encodedSize=0;
	for( int i =0; i < size; i++)
	{
		frequency[(int)message[i]]++;
	}//reads message update frequency list
	
	for(int j =0; j<256; j++)
	{
		if (frequency[j]!=0)
		{
			HuffNode* temp=new HuffNode((char)j,frequency[j]);
			theHeap->insert(temp); 
		}
	}//insert into initally empty heap
	
	while (theHeap->currentSize!=1)
	{
	  HuffNode* temp;
          HuffNode* temp2;
          theHeap->deleteMin(temp);
          theHeap->deleteMin(temp2);
          theHeap->insert(new HuffNode(temp,temp2));
                delete temp;
                delete temp2;
	}//removes top two nodes and makes a new node then reinserts the new node. Stops when only one node left. theHeap is huffman tree
	
	unsigned int mask = 0x8000000; //1 and 31 zeroes
	unsigned int codeS=0;
	printCode(theHeap->findMin(), codeS,mask,0);
	int pos =0;
	*encodedSize =0;
	int key =0;//encodedMessage key
	
	for(int i=0;i<256; i++)
	{
		
		
		if (frequency[i]>0)
		{
			encodedMessage[5*key] = (char) i;
			encodedMessage[key+1]|=((char*)&frequency[i])[0];
			encodedMessage[key+2]|=((char*)&frequency[i])[1];
			encodedMessage[key+3]|=((char*)&frequency[i])[2];
			encodedMessage[key+4]|=((char*)&frequency[i])[3];
			key++;
		}//end 
	}//end header with freq of each. 
	encodedMessage[5*key]|=0;//EOF header just char 0 count of 0
	encodedMessage[key+1]|=0;
	encodedMessage[key+2]|=0;
	encodedMessage[key+3]|=0;
	encodedMessage[key+4]|=0;
	*encodedSize+=(5*(key+1));
	int index=*encodedSize;
	int count=*encodedSize;
	
	for(int i=0; i < size; i++)
	{
		encodedMessage[index+0]|=((char*)&coded[message[i]][pos])[3];
		encodedMessage[index+1]|=((char*)&coded[message[i]][pos])[2];
		encodedMessage[index+2]|=((char*)&coded[message[i]][pos])[1];
		encodedMessage[index+3]|=((char*)&coded[message[i]][pos])[0];
		
		index =((lengths[message[i]]+pos )/8)+count;
		pos=+((lengths[message[i]])%8);
		encodedSize++;
	}//end writing to encodedMessage
	
	
	
}//end encoded
