//  Author: Kevin Nguyen & Angela Haowen Zhou
//
#include "TripsRunner.h"
#include "router.h"
#include "LinkedList.h"
#include "BinaryHeap.h"
#include "vertex.h"

Router::Router(int numCities, int numFlights, Flight *flights)
{
	numCity=numCities;
	adjList= new List<Flight*>*[5700];//try with 5700 an no hash function lateri
	HTable= new vertex*[5700];//hash table of vertices to access them in the Queue
	for (int a=0;a<5700;a++)
	{
		adjList[a]=NULL;
		HTable[a]=NULL;
	}

	for (int i=0; i<numFlights;i++)
	{
		int AIndex= (int)(flights[i].originIndex);//changing to just arrray		bool inserted=false;
		Flight* add= new Flight;
		*add=flights[i]; 
		vertex* temp = new vertex(add,~0);
		
		while (!inserted)
		{
			
			if (adjList[AIndex]==NULL)
			{
				Flight* temp;
				temp = new Flight;
				*temp=flights[i];
				adjList[AIndex]=new List<Flight*>();
				adjList[AIndex]->insert(temp,adjList[AIndex]->zeroth());
				inserted=true;
				
			}//case NEW CITY
			else if ((adjList[AIndex]->getFirst())->originIndex==flights[i].originIndex)
			{
				Flight* temp;
				temp = new Flight;
				*temp=flights[i];
				adjList[AIndex]->insert(temp,adjList[AIndex]->zeroth());
				inserted=true;
			
			}//case already exists
			else 
			{
				AIndex++;//linear probing
				if (AIndex==numCities)
					AIndex=0;//the reset
			}
		}//end while
		HTable[AIndex]=temp;//indexed by originIndex
	}//keys are origin index stores flight information into array of linked lists.	
	
	
} // Router()


void Router::findRoute(const Trip* trip, Itinerary *itinerary)
{
	itinerary->numFlights = 0;  // to be set by student
	unsigned start =trip->originIndex;
	unsigned end = trip->destinationIndex;
	unsigned short theTime;
	int flightNumber[20];
	int ind=0;
	theTime = trip->departureTime;
	dijkstra(start,theTime);
	int indexBest=end%numCity;
	while(end!=start)//when from is NULL since we set the first vertex to be NULL
	{
		
		while(HTable[indexBest]->index!=end)
		{
		indexBest++;//linear probing
			if (indexBest>=numCity)
			{
				indexBest=0;
			}
		}//gets the vertex of the end so we can trace back
		itinerary->numFlights++;

		flightNumber[ind]=HTable[indexBest]->from->flightNum;
		ind++;
		end= HTable[indexBest]->from->originIndex;//gets vertex of where it is coming from
		indexBest=end%numCity;
	}//iterates backward from destination to get which path to get
	for (int i=0;i<itinerary->numFlights;i++)
	{
		
		itinerary->flightNums[i]=flightNumber[itinerary->numFlights-1-i];
	}
   
}  // findRoute

void Router::dijkstra(unsigned start, short sTime)
{
	BinaryHeap<vertex*>Herp(numCity);
	Herp.makeEmpty();
	short Ttime;
	short theTime;
	for(int i =0; i<numCity;i++)
	{
	HTable[i]->pTime=~0;
	HTable[i]->known=false;
	Herp.insert(HTable[i]);
	}//reset table to deafult constructed state
	updateVertex(start,0,sTime);//initial point
	Herp.buildHeap();
	while(!Herp.isEmpty())
	{
		vertex* temp;
		Herp.deleteMin(temp);
		
		temp->known=true;
		Ttime=temp->theTime;
		theTime=Ttime;
		int index =(temp->index%numCity);
		while(HTable[index]->index!=temp->index)
		{
		index++;//linear probing
			if (index==numCity)
			{
				index=0;
			}
		}// this index is the same index for adjacency list
		ListItr<Flight*> adjFlights=adjList[index]->first();
		while(!adjFlights.isPastEnd())
		{
			Flight* tempFlight=adjFlights.retrieve();
			int dTimeFlight=tempFlight->departureTime;
			if(dTimeFlight-theTime>=30)
			{
				 short theflight=tempFlight->duration+dTimeFlight-theTime;
				Ttime=temp->pTime+theflight;//updates total time of trip by calculating time till next flight+ 30min wait time + flight duration
				updateVertex(tempFlight->destinationIndex,Ttime,tempFlight,((tempFlight->duration+tempFlight->departureTime)%1440));
			}//if flight is on the same day
			if(dTimeFlight-theTime<30&&dTimeFlight-theTime>=0)
			{
			             if(tempFlight->originIndex == start)
                                                       {
				short theflight=tempFlight->duration+dTimeFlight-theTime;
				Ttime=temp->pTime+theflight;//updates total time of trip by calculating time till next flight+ 30min wait time + flight duration
				updateVertex(tempFlight->destinationIndex,Ttime,tempFlight,((tempFlight->duration+tempFlight->departureTime)%1440));
                                                         
                                                       }//if the starting flight is less than 30 min

                                                       else
                                                       {
                                                        short theflight=tempFlight->duration+dTimeFlight-theTime+1440;//have to wait a whole day
				Ttime=temp->pTime+theflight;//updates total time of trip by calculating time till next flight+ 30min wait time + flight duration
				updateVertex(tempFlight->destinationIndex,Ttime,tempFlight,((tempFlight->duration+tempFlight->departureTime)%1440));
                                                       }
			}
			if (dTimeFlight-theTime<0)
			{
             				if( dTimeFlight+1440-theTime >= 30 || tempFlight->originIndex == start)
				{
				short theflight=tempFlight->duration+dTimeFlight-theTime+1440;
				Ttime=temp->pTime+theflight;//updates total time of trip by calculating time till next flight+ 30min wait time + flight duration
				updateVertex(tempFlight->destinationIndex,Ttime,tempFlight,((tempFlight->duration+tempFlight->departureTime)%1440));
				}
				else
				{
				  short theflight=tempFlight->duration+dTimeFlight-theTime+1440+1440;//add to next day
				Ttime=temp->pTime+theflight;//updates total time of trip by calculating time till next flight+ 30min wait time + flight duration
				updateVertex(tempFlight->destinationIndex,Ttime,tempFlight,((tempFlight->duration+tempFlight->departureTime)%1440));
				}
			}//if flight is on the next day
			
			adjFlights.advance();
		}// this code updates each vertex in the adjacent matrix list. 
		Herp.buildHeap();//after updating the vertices use buildheap to maintain order get lowest.
	}//should have empty heap since we visited all verticies

}

void Router::updateVertex(unsigned x, short time,Flight* pFrom,unsigned short theTime)
{
	int index=(x%numCity);
	while(HTable[index]->index!=x)
	{
		index++;//linear probing
		if (index==numCity)
		{
			index=0;
		}
	}
	if (!HTable[index]->known&&time<=HTable[index]->pTime)
	{
		HTable[index]->pTime=time;
		HTable[index]->from=pFrom;//from is the flight information it has originIndex for which city
		HTable[index]->theTime=theTime;
	}
}//For use with adjacency list
void Router::updateVertex(unsigned x, short time,unsigned short startTime)
{
	int index=(x%numCity);
	while(HTable[index]->index!=x)
	{
		index++;//linear probing
		if (index==numCity)
		{
			index=0;
		}
	}
	HTable[index]->pTime=time;
	HTable[index]->from=NULL;
	HTable[index]->theTime=startTime;
}//For use with 1st only destination only
