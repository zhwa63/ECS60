// Author: Kevin Nguyen & Angela Haowen Zhou
#ifndef ROUTER_H
#define	ROUTER_H

#include "TripsRunner.h"
#include "LinkedList.h"
#include "vertex.h"
#include "BinaryHeap.h"

class Router
{
public:
  Router(int numCities, int numFlights, Flight *flights);
  void findRoute(const Trip* trip, Itinerary *itinerary);
  void updateVertex(unsigned, short,Flight*,unsigned short);
  void updateVertex(unsigned , short,unsigned short);
  void dijkstra(unsigned, short);
private:
  int numCity;
  List<Flight*>** adjList;
  vertex** HTable;
 // BinaryHeap<vertex*>* Herp;
};

#endif	/* ROUTER_H */

