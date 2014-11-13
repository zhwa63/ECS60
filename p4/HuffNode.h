//Author:Kevin Nguyen and Angela Haowen Zhou

#ifndef HUFFNODE_H
#define HUFFNODE_H

#include <iostream>
#include<string>

using namespace std;

class HuffNode
{
  

  public:
  char letter;
  int frequency; 
  HuffNode* left, *right;
  HuffNode();
  HuffNode(HuffNode*,HuffNode*);
  HuffNode(char,int);
  ~HuffNode();
  HuffNode& operator=(const HuffNode&);
  bool operator<(const HuffNode&);
  bool operator>(const HuffNode&);
  bool isLeaf();
};

#endif  
