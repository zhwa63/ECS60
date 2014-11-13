//Author: Kevin Nguyen and Angela Haowen Zhou

#include "HuffNode.h"
using namespace std;

HuffNode::HuffNode()
{
  letter='0';
  frequency=0; 
  left=NULL;
  right=NULL;
}
HuffNode::HuffNode(HuffNode* left, HuffNode* right)
{
  this->left = left;
  this->right = right;
  frequency = left->frequency+right->frequency;
  letter = -1;
}//internal node constructor

HuffNode::HuffNode(char Let, int freq)
{
  letter = Let;
  frequency = freq;
  left = right = NULL;
}//leaf node constructor

HuffNode::~HuffNode()
{
	delete left;
	delete right;
	frequency = -1;
	letter = -1;	
}//end destructor

HuffNode& HuffNode::operator=(const HuffNode& rhs)
{
	if(!(this==&rhs))
	{
		letter = rhs.letter;
		left=rhs.left;
		right=rhs.right;
		frequency=rhs.frequency;
	}
	return *this;
}//end copy operator

bool HuffNode::operator<(const HuffNode& rhs)
{
	return(frequency<rhs.frequency);
}//end compare
bool HuffNode::operator>(const HuffNode& rhs)
{
	return(frequency>rhs.frequency);
}//end compare

bool HuffNode::isLeaf()
{
	return (left==NULL);//complete graph must have left child before having a right.
}

