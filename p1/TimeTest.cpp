#include "CPUTimer.h"
#include "dsexceptions.h"
#include "LinkedList.h"
#include "StackAr.h"
#include "CursorList2.h"
#include "QueueAr.h"
#include "StackLi.h"
#include "vector.h"
#include "SkipList.h"
#include <iostream>
#include <fstream>
#include <string>

vector<CursorNode <int> > cursorSpace(250000);
using namespace std; 

void RunList(string FileName)
{
  ifstream File;
  File.open(FileName.c_str());
 
  List<int> LK;
  ListItr<int> p;
  string line;
  if( File.is_open())
  {
    File.seekg(File.beg);
    getline(File,line);
    while(File.good())
    {
      
      getline(File,line,' ');
      if  (line[0]=='i')
      {
       p=LK.zeroth();
       int insertNumber;
       insertNumber= atoi(line.substr(1,line.length()-1).c_str());//convert string to integer
       LK.insert(insertNumber,p);
      }//end if	
      if (line[0]=='d')
      {
       int delNumber;
       delNumber= atoi(line.substr(1,line.length()-1).c_str());//convert string to integer
       LK.remove(delNumber);
      }//end if deletion
    }//end while
  }//end if file is open
  else
  {
    cout<<"File did not open"<<endl;
  }//end else
 File.close();
}//end RunList

void RunCursorList(string FileName)
{
  ifstream File;
  File.open(FileName.c_str());

  CursorList<int>ADT(cursorSpace);
  CursorListItr<int> p(ADT);
  string line;
  if( File.is_open())
  {
    File.seekg(File.beg);
    getline(File,line);
    while(File.good())
    {
      
      getline(File,line,' ');
      if  (line[0]=='i')
      {
       //p=ADT.zeroth();
       int insertNumber;
       string number= line.substr(1,line.length()-1);//convert command to string of number
       insertNumber= atoi(number.c_str());//convert string to integer
       ADT.insert(insertNumber,ADT.zeroth());
      }//end if	
      if (line[0]=='d')
      {
       int delNumber;
       delNumber= atoi((line.substr(1,line.length()-1)).c_str());//convert string to integer
       ADT.remove(delNumber);
      }//end if deletion
    }//end while
  }//end if file is open
  else
  {
    cout<<"File did not open"<<endl;
  }
  File.close();
}//end CursorList

void RunStackAr(string FileName)
{
  ifstream File;
  File.open(FileName.c_str());

  StackAr<int>ADT(250000);
  string line;
  if( File.is_open())
  {
    File.seekg(File.beg);
    getline(File,line);
    while(File.good())
    {
      
      getline(File,line,' ');
      if  (line[0]=='i')
      {
       int insertNumber;
       string number= line.substr(1,line.length()-1);//convert command to string of number
       insertNumber= atoi(number.c_str());//convert string to integer
       ADT.push(insertNumber);
      }//end if	
      if (line[0]=='d')
      {
       ADT.pop();
      }//end if deletion
    }//end while
  }//end if file is open
  else
  {
    cout<<"File did not open"<<endl;
  }
  File.close();
}//end StackAR

void RunStackLi(string FileName)
{
  ifstream File;
  File.open(FileName.c_str());

 StackLi<int>ADT;
  string line;
  if( File.is_open())
  {
    File.seekg(File.beg);
    getline(File,line);
    while(File.good())
    {
      
      getline(File,line,' ');
      if  (line[0]=='i')
      {
       int insertNumber;
       string number= line.substr(1,line.length()-1);//convert command to string of number
       insertNumber= atoi(number.c_str());//convert string to integer
       ADT.push(insertNumber);
      }//end if	
      if (line[0]=='d')
      {
       ADT.pop();
      }//end if deletion
    }//end while
  }//end if file is open
  else
  {
    cout<<"File did not open"<<endl;
  }
  File.close();
}//end StackAR


void RunQueueAr(string FileName)
{
  ifstream File;
  File.open(FileName.c_str());

  Queue<int>ADT(250000);
  string line;
  if( File.is_open())
  {
    File.seekg(File.beg);
    getline(File,line);
    while(File.good())
    {
      
      getline(File,line,' ');
      if  (line[0]=='i')
      {
       int insertNumber;
       string number= line.substr(1,line.length()-1);//convert command to string of number
       insertNumber= atoi(number.c_str());//convert string to integer
       ADT.enqueue(insertNumber);
      }//end if	
      if (line[0]=='d')
      {
       ADT.dequeue();
      }//end if deletion
    }//end while
  }//end if file is open
  else
  {
    cout<<"File did not open"<<endl;
  }
  File.close();
}//end QueueAr

void RunSkipList (string FileName)
{
  ifstream File;
  File.open(FileName.c_str());

  SkipList<int>ADT(-1,250000);
  if( File.is_open())
  {
    File.seekg(File.beg);
    string line;
    getline(File,line);
    while(File.good())
    {
      
      getline(File,line,' ');
      if  (line[0]=='i')
      {
       int insertNumber;
       string number= line.substr(1,line.length()-1);//convert command to string of number
       insertNumber= atoi(number.c_str());//convert string to integer
       ADT.insert(insertNumber);
      }//end if	
      if (line[0]=='d')
      {
       int delNumber;
       delNumber= atoi((line.substr(1,line.length()-1)).c_str());
       ADT.deleteNode(delNumber);
      }//end if deletion
    }//end while
  }//end if file is open
  else
  {
    cout<<"File did not open"<<endl;
  }
  File.close();
}//end QueueAr

int main()
{
  string filestr;
  CPUTimer ct = CPUTimer(); 
  int choice;
  cout<<"Filename >> ";
  cin>> filestr;
  
  
  
  
  do
  {
   
   cout<<"      "<<"ADT Menu"<<endl;
  cout<<"0. Quit"<<endl;
  cout<<"1. LinkedList"<<endl;
  cout<<"2. CursorLIst"<<endl;
  cout<<"3. StackAr"<<endl;
  cout<<"4. StackLi"<<endl;
  cout<<"5. QueueAr"<<endl;
  cout<<"6. SkipList"<<endl;
  cout<<"your choice >> ";

    cin>> choice;
    ct.reset();
    switch (choice)
    {
      case 0:
      return 0;
      break;

      case 1:
      RunList(filestr);
      break;//LinkedList
      case 2:
      RunCursorList(filestr);
      break;
      case 3:
      RunStackAr(filestr);
      break;
      case 4:
      RunStackLi(filestr);
      break;
      case 5:
      RunQueueAr(filestr);
      break;
      case 6:
      RunSkipList(filestr);
      break;
    }//end switch
    cout << "CPU time: " << ct.cur_CPUTime()<<"\n"<< endl;
  }while (choice >0);
  
  return 0;
}//end main
