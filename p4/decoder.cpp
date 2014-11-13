//Author: Kevin Nguyen and Haowen Angela Zhou

#include "decoder.h"


Decoder::Decoder()
{
  theHeap= new BinaryHeap<HuffNode*>(256);// the heap to initally hold the frequencies
}


Decoder::~Decoder()
{
	delete theHeap;
}

void Decoder::decode(const unsigned char* encodedMessage,const int encodedSize,unsigned char* decodedMessage, int *decodedSize)
{
	int dIndex=0;// initialize decoded message index      
        int index=0;//index in encoded message
	int pos=0;//bit position
	for(int i=0;i<256;i++)
	{
		if(encodedMessage[5*i]==0&&encodedMessage[5*i+1]==0&&encodedMessage[5*i+2]==0&&encodedMessage[5*i+3]==0&&encodedMessage[5*i+4]==0)
		{
			index=(5*i)+5;// puts index at end of header
			break;
		}//reached EOF
		
		else
		{
			unsigned int readFreq=0;
			((char*)&readFreq)[0]|=encodedMessage[5*i+1];
			((char*)&readFreq)[1]|=encodedMessage[5*i+2];
			((char*)&readFreq)[2]|=encodedMessage[5*i+3];
			((char*)&readFreq)[3]|=encodedMessage[5*i+4];
			HuffNode* temp = new HuffNode(encodedMessage[5*i],readFreq);
			theHeap->insert(temp); 
			
		}//making of original tree with leaf nodes of frequency only.
	//}//make original
	while (theHeap->currentSize!=1)
	{
          HuffNode* temp;
          HuffNode* temp2;
          theHeap->deleteMin(temp);
          theHeap->deleteMin(temp2);
          theHeap->insert(new HuffNode(temp,temp2));
                delete temp;
                delete temp2;
	}//removes top two nodes
	
	
	pos=0;
	HuffNode* tempNode = theHeap->findMin();//gets root
	unsigned char mask= 0x80;//1 and 7 zeroes
		while (index<encodedSize)
		{
			
			if(tempNode->isLeaf())
			{
			decodedMessage[dIndex]=tempNode->letter;
			dIndex++;
			tempNode=theHeap->findMin();
			}//is at leaf reset tempNode to root
			
			if ((encodedMessage[index]&mask)==0)
			{
				tempNode=tempNode->left;
				mask>>=1;
				pos++;
			}
			else if ((encodedMessage[index]&mask)==1)
			{
				tempNode=tempNode->right;
				mask>>=1;
				pos++;
			}
			if (pos==8)
			{
				mask=0x80;
				index++;
			}//end of reading first byte so reset mask and move to next byte.
		}//loop to continue until we read through the encoded message
	}//end for
	*decodedSize=dIndex;
}//end decoder


