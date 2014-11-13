//Author: Kevin Nguyen, Angela(Haowen) Zhou

#include <iostream>
#include "BTree.h"
#include "BTreeNode.h"
#include "LeafNode.h"
#include "InternalNode.h"
using namespace std;

BTree::BTree(int ISize, int LSize):internalSize(ISize), leafSize(LSize)
{
  root = new LeafNode(LSize, NULL, NULL, NULL);
} // BTree::BTree()


void BTree::insert(const int value)
{
    BTreeNode* split= root->insert(value);
    if (split!=NULL)
    {
        BTreeNode* oldRoot= root;
        root = new InternalNode(internalSize,leafSize,NULL,NULL,NULL);
        static_cast<InternalNode*>(root)->insert(oldRoot,split);
    } //end if root splits
    

  // students must write this
} // BTree::insert()


void BTree::print()
{
  BTreeNode *BTreeNodePtr;
  Queue<BTreeNode*> queue(1000);

  queue.enqueue(root);
  while(!queue.isEmpty())
  {
    BTreeNodePtr = queue.dequeue();
    BTreeNodePtr->print(queue);
  } // while
} // BTree::print()
