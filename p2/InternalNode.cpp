//Author: Kevin Nguyen, Angela(Haowen) Zhou

#include <iostream>
#include "InternalNode.h"

using namespace std;

InternalNode::InternalNode(int ISize, int LSize,
  InternalNode *p, BTreeNode *left, BTreeNode *right) :
  BTreeNode(LSize, p, left, right), internalSize(ISize)
{
  keys = new int[internalSize]; // keys[i] is the minimum of children[i]
  children = new BTreeNode* [ISize];
} // InternalNode::InternalNode()


int InternalNode::getMinimum()const
{
  if(count > 0)   // should always be the case
    return children[0]->getMinimum();
  else
    return 0;
} // InternalNode::getMinimum()

void InternalNode::add(int value,BTreeNode* childrenNode)
{
     if (keys[0]<1)
     {
         keys[0]=value;
         children[0]=childrenNode;
     }//end if to add to an empty list
	if (value<keys[0])
     {
         for(int j = internalSize-1; j>0; j--)
         {
             keys[j] = keys[j-1];
             children[j]= children[j-1];
         }//end for to shift everything down 
		 keys[0]=value;
                 children[0]=childrenNode;
     }//moves everything down assumes values has space. Then the first space would be the new value.
     if(value>keys[count-1])
     {
         keys[count]=value;
         children[count]=childrenNode;
     }//end if new value is greater than any other
     else
	{
	    for(int i = 0; i < count; i++)
	    {
	      if( value > keys[i]&& value < keys[i+1])
	      {
	   	for(int j = internalSize-1; j> i; j--)
		{
		  keys[j] = keys[j-1];
		children[j]= children[j-1];
		}//end for
		  keys[i+1] = value;
		  children[i+1]= childrenNode;          
		}//end if      
	    }//end for
	}//end else
count++;
 }//add()

InternalNode*  InternalNode::split(int value,BTreeNode* childrenNode)
{
  InternalNode* sNode = new InternalNode(internalSize,leafSize,parent,this,this->rightSibling);
  if (rightSibling!=NULL)
  {
    rightSibling->setLeftSibling(sNode);
  }// if there is one to the right already
  setRightSibling(sNode);
  
  if(value > keys[(internalSize-1)/2])
  {
     for(int i = 0; ((internalSize-1)/2+i+1)<=internalSize-1; i++)
     {
       keys[i] = children[i]->getMinimum();
       sNode->keys[i] = children[(internalSize-1)/2+i+1]->getMinimum();
       sNode->count++;
       sNode->children[i]=this->children[(internalSize-1)/2+i+1];
       keys[(internalSize-1)/2+i+1] = NULL;
       children[(internalSize-1)/2+i+1]=NULL;
       count--;
     }
     sNode->add(value,childrenNode);// in begining of new;
  }

  else
  {
     for(int i=0;(((internalSize-1)/2+i+1)<=internalSize-1); i++)
     {
       keys[i] = children[i]->getMinimum();//first half of indexes
       sNode->keys[i] = children[(internalSize-1)/2+i+1]->getMinimum();//bigger half of indexes
       sNode->children[i]=this->children[(internalSize-1)/2+i+1];
       sNode->count++;
       keys[(internalSize-1)/2+i+1] = NULL;
       children[(internalSize-1)/2+i+1]=NULL;
       count--;
     }     
     add(value,childrenNode);
  }      
  return sNode;
}

InternalNode* InternalNode::updateKey(int value, int index)
{
    BTreeNode* bTree = children[index]->insert(value);
         
    if(bTree==NULL)//insertion and check
    {

      for(int i = 0; i<count; i++)
      {
        keys[i] = children[i]->getMinimum();
        
      }
        return NULL;
    }//updates the keys for same number of children aka insertion didnt cause a split
    else
     {
         if (count>=internalSize)
             return split(bTree->getMinimum(),bTree);
         else
         {
             for(int i = internalSize; i>index;i--)
	     {
		children[i]=children[i-1]; 
	     }
 	     children[index+1]=bTree;
	     count++;

             //count=0;//we remake the keys so set to zero.
             for(int i = 0; i<count; i++)
             {
                 keys[i] = children[i]->getMinimum();
                 
             }
             return NULL;
         }//end else as long as there are children we will update the keys
         
     }// if more children we check to see if there is room if there is room same as above we add
}//end method

InternalNode* InternalNode::insert(int value)
{
   if(value<keys[0]||count==0)
   {
    	return updateKey(value,0);
   }
   else
  {
   for(int i = 1; i<=count-1; i++)
   {
    if(value>keys[i-1] && value <keys[i])
    {
    	return updateKey(value,i-1);
    }
   } 
   if(value>keys[count-1])
    {
    	return updateKey(value,count-1);
    }
  }//end method
/* 
  if(count < leafSize)
  { 
    add(value);
  }//end if

      else if(leftSibling != 0 && (((InternalNode*)leftSibling)->count < leafSize))
     {
      InternalNode* lSibling = static_cast <InternalNode*>(leftSibling); 
     lSibling->keys[lSibling->count] = keys[0];

     for(int i = 1; i < count; i++)
    {
      keys[i-1] = keys[i];
    }
     add(value);

    }//end else if         

  else if(((InternalNode*)leftSibling)->count == leafSize || leftSibling == 0)
   {
      if(rightSibling != NULL && (((InternalNode*)rightSibling)-> count < leafSize))
      {
       InternalNode* rSibling = static_cast <InternalNode*>(rightSibling); 
       rSibling->add(keys[count-1]);
       add(value);
      }     
      else
      {
       return split(value);       
      }
  }


 // students must write this
*/ 
  return NULL; // to avoid warnings for now.
} // InternalNode::insert()

void InternalNode::insert(BTreeNode *oldRoot, BTreeNode *node2)
{ // Node must be the root, and node1
  //InternalNode* root = new InternalNode(internalSize,leafSize, NULL,NULL,NULL);
  children[0]=oldRoot;
  children[1]=node2;
  keys[0]=oldRoot->getMinimum();
  keys[1]=node2->getMinimum();
  count+=2;

 // students must write this
} // InternalNode::insert()

void InternalNode::insert(BTreeNode *newNode) // from a sibling
{
  // students may write this
} // InternalNode::insert()

void InternalNode::print(Queue <BTreeNode*> &queue)
{
  int i;

  cout << "Internal: ";
  for (i = 0; i < count; i++)
    cout << keys[i] << ' ';
  cout << endl;

  for(i = 0; i < count; i++)
    queue.enqueue(children[i]);

} // InternalNode::print()


