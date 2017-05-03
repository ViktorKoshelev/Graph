#include "Graph.h"
Graph::Graph()
{
    graph = new int*[2];
    graph[0] = new int[2];
    graph[1] = new int[2];
    graph[0][0] = 0;
    graph[0][1] = 1;
    graph[1][0] = 1;
    graph[1][1] = 0;
    size = 2;
}


Graph::~Graph()
{
}

Graph::Graph(int s, int** m)
{
    if (!m || !s)
        throw "Matrix is empty";
    if (s < 0)
        throw "Size is non-negative";

    size = s;
    graph = new int*[size];
    for (int i = 0; i < size; i++)
        graph[i] = new int[size];
    print();
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (m[i][j]<0)
                throw "Element is negative";
            else
                graph[i][j] = m[i][j];

}

void Graph::print()
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
            cout << graph[i][j]<< " ";
        cout << endl;
    }
}

int Graph::getSize()
{
    return size;
}

int Graph::getAllArcs()
{
    int k = 0;
    for (int i = 0; i < size; i++)
        k += getArcsByNode(i);
    return k/2;
}

int Graph::getArcsByNode(int n)
{
    int k = 0;
    for (int i = 0; i < size; i++)
        if (graph[n][i]) k++;
    return k;
}

int* Graph::deikstra(int n)
{
    int self = n;
    int* paths = new int[size];
    for (int i = 0; i < size; i++)
        paths[i] = 0;

    bool* flags = new bool[size];
    for (int i = 0; i < size; i++)
        flags[i] = false;

    int newN;

    while (!flags[n])
    {
        flags[n] = true;
        int k = 0;

        for (int i = 0; i < size; i++)
        {
            if (i == n || i == self)
                continue;
            if ((!paths[i] || paths[i] > paths[n] + graph[n][i]) && graph[n][i] > 0 ) //find shortest way
            {
                paths[i] = paths[n] + graph[n][i];
            }
            if ((!k || k > graph[n][i]) && graph[n][i] > 0 && !flags[i])
            {
                k = graph[n][i];
                newN = i;
            }
        }
        n = newN;
        if (flags[n]==true) // all nodes near are marked
        {
            k = 0;
            for(int i = 0; i < size; i++)
                if (flags[i]==false) // node isn't mark
                {
                    bool out = false;
                    for (int j = 0; j < size; j++) // find shortest way from marked node
                        if (flags[j] && (!k || k > paths[j] + graph[j][i]) && graph[j][i] > 0)
                        {
                            k = graph[j][i]; // shortest way to i node
                            newN = j;
                            out = true;
                        }
                    if (out)
                    {
                        n = i;
                        paths[n] = paths[newN] + k;
                        break;
                    }
                }
        }
    }
    return paths;
}

bool Graph:: operator< (Graph& g1)
{
    if(getSize() < g1.getSize())
        return true;
    return false;
}

istream& operator >> (istream& is, Graph& g)
{
    is >> g.size;
    if (g.size < 1)
        throw "Size less than 0";
	g.graph = new int*[g.size];
	for (int i = 0; i < g.size; i++)
		g.graph[i] = new int[g.size];
	for (int i = 0; i < g.size; i++)
		{
			for (int j = 0; j < g.size; j++)
			{
				is >> g.graph[i][j];
                if (g.graph[i][j]<0)
                    throw ("Element is negative");

			}
		}
    return is;
}

ostream& operator << (ostream& os, const Graph& g)
{
    for (int i = 0; i < g.size; i++)
    {
        for (int j = 0; j < g.size; j++)
            os << g.graph[i][j]<< " ";
        os << endl;
    }
    return os;
}

int** Graph::getMatrix()
{
    return graph;
}
