#include "Graph.h"
#include <iostream>
#include <fstream>
#include <list>
#include <iterator>
using namespace std;

void printResults(Graph g)
{
    g.print();
    cout << endl;
    cout << "Все ребра:" << g.getAllArcs() << endl;
    for (int i = 0; i < g.getSize(); i++)
        cout << "У " << i+1 << " точки ребер:" << g.getArcsByNode(i) << endl;
    for (int i = 0; i < g.getSize(); i++)
    {
        int* m = g.deikstra(i);
        for (int j = 0; j < g.getSize(); j++)

            cout << "Дейкстра из " << i+1 << " в " << j+1 << ": " << m[j] << endl;
    }
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "rus");
    ifstream fin("Matrix.txt");
    list<Graph> graphs;
    list<Graph> :: iterator i;
    Graph g;
    try
    {
        while (!fin.eof())
        {
            fin >> g;
            graphs.push_back(g);
        }
    }
    catch(const char* str)
    {
        cout << str;
        return 0;
    }
    cout << "Список: \n";
    copy(graphs.begin(), graphs.end(), ostream_iterator<Graph>(cout," \n"));
    graphs.sort();
    cout << "Список sort: \n";
    copy(graphs.begin(), graphs.end(), ostream_iterator<Graph>(cout," \n"));
    cout << "--------------------------\n";
    for (i = graphs.begin(); i != graphs.end(); i++)
        printResults(*i);
    return 0;

}
