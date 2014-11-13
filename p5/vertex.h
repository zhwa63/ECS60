// Author: Kevin Nguyen & Angela Haowen Zhou
#ifndef VERTEX_H
#define	VERTEX_H

#include "TripsRunner.h"
#include <iostream>
using namespace std;

class vertex
{
public:

	vertex();
	vertex(Flight*,unsigned short);
	bool operator<( vertex&);
    bool operator>( vertex&);
  unsigned short pTime;
  Flight* from;
  bool known;
  unsigned index;
  unsigned short theTime;
 
private:
 
};

#endif	/* VERTEX_H */

