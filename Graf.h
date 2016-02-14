#include<iostream>
#include<list>
#include<vector>
#include<stack>
#include<string>
#include<fstream>
#include<iomanip>
#include<stdlib.h>
#include<ctime>
using namespace std;


class Vertex
{
private:


public:
unsigned index;
bool visited;
	typedef struct
	{
	public:
		Vertex *end; //wierzcholek do ktorego idzie krawedz
		double weight;
	}Edge;
	double x, y;
	vector<Edge> edges;

	Vertex(int i, double nX, double nY) : visited(false), index(i), x(nX), y(nY) {};
	Vertex(){};
	int getIndex()
	{
		return index;
	}
	void Visit()
	{
		visited = true;
	}
	bool checkstatus()
	{
	  return visited;
	}
	void notVisited()
	{
	 visited=false;
    }

	void pushEdge(Edge e)
	{
		edges.push_back(e);
	}


};



class Graph
{
public:
	vector<Vertex> vertices;
	void addVertex(int i, double x, double y)
	{
		//cout << "\nDodaje wierzcholek: " << i << " " << x << " " << y;
		vertices.push_back(Vertex(i, x, y));
	}
	void addEdge(Vertex *v, Vertex *end, double weight)
	{
		if (vertices.empty())
		{
			//cout << "\npusty graf";
			return;
		}
		if (!v || !end)
		{
			//cout<< "\nwierzcholek " << v <<" nie istnieje";
			return;
		}


		vector<Vertex::Edge>::iterator it;
		for (it =v->edges.begin(); it != v->edges.end(); it++)
		{//gdy taka krawedz juz istnieje to zmien jej wage
			if (it->end == end)
			{
				it->weight = weight;
				return;
			}
		}
		//cout << "\nDodaje krawedz " << v << "->" << end << " o wadze " << weight;
		Vertex::Edge nEdge;
		nEdge.end = end;
		nEdge.weight = weight;
		v->pushEdge(nEdge);
	}

void clearvisit()
{
  for ( unsigned n=0; n < vertices.size(); ++n)
  {
   vertices[n].visited=false;
  }

}

bool IsShifted(vector<unsigned> newCycle, vector<unsigned> validCycle)
{
	if (newCycle.size() == validCycle.size())
	{
		unsigned i = 0;
		newCycle.pop_back();				// usuniecie ostatniego wyrazu
		validCycle.pop_back();
		unsigned size = validCycle.size();
		while (i < size  && newCycle[i] != validCycle[0]) ++i;
		//cout<<i<<"\n";
		if (i<size)
		{
			for (unsigned j = 0; j < size; ++j,++i)
			{
				if (validCycle[j] != newCycle[i%size]) return false;
			}
			return true;
		}
		else return false;
	}
	return false;
}

double find_edge_weight(unsigned from, unsigned to)
{
	for (unsigned k = 0; k < vertices[from].edges.size(); ++k)
	{
		if (vertices[from].edges[k].end->getIndex() == to)
		{
			return vertices[from].edges[k].weight;
		}
	}
	return 0.0;
}


double sum_weight(vector<unsigned> & path)
{
 unsigned length=path.size();
 length--;
 double Waga=0.0;
 unsigned i=0;
 while(i<length)
 {
  Waga=Waga+find_edge_weight(path[i],path[i+1]);
  i++;
 }
 return Waga;
}



void DFSfindCycle(list<vector<unsigned> > &ret,unsigned start, unsigned current , vector<unsigned>& S)
{

  vertices[current].Visit();
  S.push_back(current);

  for(unsigned u=0;u<vertices[current].edges.size();++u)
    {
      unsigned current_index=vertices[current].edges[u].end->getIndex();
      if(vertices[current].edges[u].end->getIndex()==start)
      {
       S.push_back(vertices[current].edges[u].end->getIndex());

        if((S.size() % 2))
        {
         list<vector<unsigned> >::iterator iter = ret.begin();
         while (iter != ret.end() && !IsShifted(S, *iter))
          ++iter;

         if (iter == ret.end())
         {
            ret.push_back(S);
         }
        }
        S.pop_back();
      }
     else if(vertices[current_index].checkstatus()==false)
     {
       DFSfindCycle(ret,start,current_index,S);
     }
   }

   S.pop_back();
   vertices[current].notVisited();


}



void run()
{
     list <vector<unsigned> > ret;
     vector<unsigned> T;
     for(unsigned i=0; i < vertices.size() ; ++i)
     {
       clearvisit();
       DFSfindCycle(ret,i,i,T);
       T.clear();
      }

      if(!ret.empty())
      {
       for (list<vector<unsigned> >::iterator it = ret.begin(); it != ret.end(); ++it)
       {
				for (unsigned j = 0; j < it->size(); ++j)
				{
                    cout << (*it)[j] << " ";
				}
				cout<<sum_weight(*it)<<"\n";
        }
		}
		else cout << "Brak cykli\n";
}


};







