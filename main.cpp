#include<iostream>
#include<vector>
#include<stack>
#include<string>
#include<fstream>
#include<stdlib.h>
#include<ctime>
#include "Graf.h"

using namespace std;


int main()
{
     Graph G;

	stack<unsigned> S;

	int v = 0, e = 0;   //liczba wierzchołkow i krawedzi

    string tmp;



	while (getline(cin,tmp))
	{
        string l1, l2, l3;
		string::iterator it;

		it = tmp.begin();
		while (it != tmp.end() && *it != ' ')
		{
			l1.push_back(*it);
			++it;
		}
		if (it != tmp.end())
		{
			++it;
		}//przeskocz spacje
		while (it != tmp.end() && *it != ' ')
		{
			l2.push_back(*it);
			++it;
		}
		if (it != tmp.end())//jesli jest trzecia wartosc
		{
			++it;
			while (it != tmp.end())
			{
				l3.push_back(*it);
				++it;
			}
		}
		if (l3.empty() && e==0)//brak trzeciej wartosci -> wczytalismy wierzcholek
		{


			double i = atof(l1.c_str()); //c_str zwraca tablice znakow
			double j = atof(l2.c_str());
			G.addVertex(v, i, j);

			++v;
		}
		else if (!l3.empty())//w innym przypadku byla to krawedz
		{
			++e;
			int i = atoi(l1.c_str());
			int j = atoi(l2.c_str());
			double k = atof(l3.c_str());
			G.addEdge(&(G.vertices[i]), &(G.vertices[j]), k);

		}
		else//skonczylismy wczytywac druga grupe
			break;
	}

    /*cout<<G.vertices[5].edges[0].end->getIndex()<<"\n";

    for(int k=0; k<G.vertices.size(); k++)
    {
    cout<<G.vertices[k].index<<"\n";
     for(int p=0; p<G.vertices[k].edges.size();p++)
      {
       cout<<G.vertices[k].edges[p].end->getIndex()<< " waga: "<<G.vertices[k].edges[p].weight<<" ";
      }
      cout<<endl;
    }*/

    G.run();




	return 0;
}
