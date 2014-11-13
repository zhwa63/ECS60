#include "puzzle.h"
#include <cstring>

using namespace std;
struct toSolve
{
  int row;
  int col;
  int square;
  char val;
}places[81];

Puzzle::Puzzle(const char grid[][9])
{
  int index=0;
  for(int i=0;i<9;i++)
    for(int j=0;j<9;j++) 
    {
      if (grid[i][j]=='*')
      {
        places[index].row=i;
        places[index].col=j;
        places[index].square=((i/3)*3+(j/3));
        places[index].val='0';
        index++;
      }//read the grid
    }//end for   
}//method

void Puzzle::solve(char grid[][9])
{
 int writeGrid=0;
 int solC=0;
 while(places[solC].val!=NULL)
  {
    if (places[solC].val=='0')
    {
      if (placeNumber(solC,'1',grid))
      {
       grid[places[solC].row][places[solC].col]=places[solC].val;
       solC++;
      }
      else 
      {
        places[solC].val='0';
        grid[places[solC].row][places[solC].col]='*';
        solC--;
       }
     }//end first pass
    else
     {
         if (placeNumber(solC,places[solC].val,grid))
         {
             grid[places[solC].row][places[solC].col]=places[solC].val;
             solC++;
         }
         else
         {
              places[solC].val='0';
                 grid[places[solC].row][places[solC].col]='*';
                 solC--;
         }
     }
  }//end while
 while(places[writeGrid].val!=NULL)
 {
   grid[places[writeGrid].row][places[writeGrid].col]=(char)places[writeGrid].val;
   writeGrid++;
 }//end while

}//end solve

bool Puzzle::placeNumber(int pos, char start, char solveGrid[][9])
{
  for(;(int)start<58;(int)start++)//58 is ascii value for : which is after 9
    if (checkRow(places[pos].row,start,solveGrid)&&checkCol(places[pos].col,start,solveGrid)&&checkSquare(places[pos].square,start,solveGrid))
   {
    places[pos].val=start;
   return true;
   }//check if this is a valid number
return false;

}//make sure to use start >=1

bool Puzzle::checkSquare(int square,char num, char solveGrid[][9])
{
   for (int i=0;i<9;i++)
      for(int j=0;j<9;j++)
       if ((i/3)*3+(j/3)==square)
         if(solveGrid[i][j]==num)
           return false;
   return true;
}//check square to see if number exists already

bool Puzzle::checkRow(int row,char num, char solveGrid[][9])
{
  for (int i=0;i<9;i++)
    if (solveGrid[row][i]==num)
     return false;
  return true;
}//check row to see if number exists already

bool Puzzle::checkCol(int col,char num, char solveGrid[][9])
{
  for (int i=0;i<9;i++)
    if (solveGrid[i][col]==num)
      return false;
  return true;
}
