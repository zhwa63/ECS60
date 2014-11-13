//Author: Kevin Nguyen, Angela(Haowen) Zhou

#include <iostream>
#include "LeafNode.h"
#include "InternalNode.h"
#include "QueueAr.h"

using namespace std;


LeafNode::LeafNode(int LSize, InternalNode *p,
  BTreeNode *left, BTreeNode *right) : BTreeNode(LSize, p, left, right)
{
  values = new int[LSize];
}  // LeafNode()



int LeafNode::getMinimum()const
{
  if(count > 0)  // should always be the case
    return values[0];
  else
    return 0;

} // LeafNode::getMinimum()

void LeafNode::add(int value)
{
     if (values[0]<1)
     {
         values[0]=value;
     }//end if to add to an empty list
     if (value<values[0])
     {
         for(int j = leafSize-1; j>0; j--)
         {
             values[j] = values[j-1];
         }//end for to shift everything down 
		 values[0]=value;
     }//moves everything down assumes values has space. Then the first space would be the new value.
     if(value>values[count-1])
     {
         values[count]=value;
     }//end if new value is greater than any other
         
     for(int i = 0; i < count; i++)
     {
      if( value > values[i]&& value < values[i+1])
      {
        for(int j = leafSize-1; j> i; j--)
        {
          values[j] = values[j-1];
        }//end for
          values[i+1] = value;          
      }//end if
    }//end for if value is in between first and last value
    count++;//increments count because we added
 }//add()

LeafNode*  LeafNode::split(int value)
{
  LeafNode* sNode = new LeafNode(leafSize,parent,this,rightSibling);
  if (rightSibling!=NULL)
  {
    rightSibling->setLeftSibling(sNode);
  }// if there is one to the right already
  setRightSibling(sNode);

  if(value > values[(leafSize-1)/2])
  {
      int moved=0;
     for(int i = 0; ((leafSize-1)/2+i+1)<=leafSize-1; i++)
     {
         
       sNode->values[i] = values[(leafSize-1)/2+i+1];
         sNode->count++;
         values[(leafSize-1)/2+i+1]=NULL;
         moved++;
     }//end for to move half of original to splited node
      count-=moved;//subtract how many we moved from old to new.
      sNode->add(value);//new value goes in splitted
     
  }//end if new value is greater than half of array so it would go in new splitted array

  else
  {
      int moved=0;
     for(int i = 0; values[(leafSize-1)/2+i]!=NULL; i++)
     {
       sNode->values[i] = values[(leafSize-1)/2+i];
         sNode->count++;
         values[leafSize-1/2+i]=NULL;
         moved++;
     }     
      count-=moved;
     add(value);
  }// if it is less than half of the array it would go on the old array
  return sNode;
}//end else to move more than half of original over then add new value to original 

LeafNode* LeafNode::insert(int value)
{
  
  if(count < leafSize)
  { 
    add(value);
    return NULL; // to avoid warnings for now.
    
  }//end if
  else
  {
      if(leftSibling != 0 && (((LeafNode*)leftSibling)->count < leafSize))
     {
         LeafNode* lSibling = static_cast <LeafNode*>(leftSibling);
         lSibling->values[lSibling->count] = values[0];
         lSibling->count++;
         count--;// pawned off only one
         for(int i = 1; i <= leafSize-1; i++)
         {
           values[i-1] = values[i];
         }//shifts to front since we gave first away makes last element NULL
         values[leafSize-1]=NULL;
         add(value);// adds new element since there is space
         return NULL;
     }//end  if

   if(leftSibling == NULL ||((LeafNode*)leftSibling)->count == leafSize)
   {
      if(rightSibling != NULL && (((LeafNode*)rightSibling)-> count < leafSize))
      {
       LeafNode* rSibling = static_cast <LeafNode*>(rightSibling); 
       rSibling->add(values[count-1]);//give right largest of original
          count--;//pawned off to rightSibling
       add(value);
          return NULL;
      }     
      else
       return split(value);//if both cases above fail then we must split and return the splited node
  }//end if
  }//end else if inital is full

  

  // students must write this

}  // LeafNode::insert()

void LeafNode::print(Queue <BTreeNode*> &queue)
{
  cout << "Leaf: ";
  for (int i = 0; i < count; i++)
    cout << values[i] << ' ';
  cout << endl;
} // LeafNode::print()


