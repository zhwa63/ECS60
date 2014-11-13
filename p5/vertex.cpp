//  Author: Kevin Nguyen & Angela Haowen Zhou
#include "vertex.h"


vertex::vertex()
{

}
vertex::vertex(Flight* x, unsigned short Time): pTime(Time),from(NULL),known(false),index(x->originIndex)
{
}

bool vertex::operator<( vertex& x)
{
	return (pTime<x.pTime);
}

bool vertex::operator>( vertex& x)
{
	return (pTime>x.pTime);
}
