#include <fstream>
#include <list>
#include <iostream>
#include <queue>
#include <vector>
#include <set>
class Graph
{
public:
    int numVertices, numEdges, startVertex;
    list<int> *adjList;
    bool *visitedNodes;
    vector<set<int>> groups;
    int groupCount;

public:
    Graph() : numVertices(0), numEdges(0), startVertex(0), groupCount(0) {}
    Graph(int vertices, int edges) : numVertices(vertices), numEdges(edges)
    {
        adjList = new list<int>[vertices];
        visitedNodes = new bool[vertices];
        for (int i = 0; i < vertices; i++)
        {
            visitedNodes[i] = false;
        }
    }
    void findGroupsUsingQueue()
    {
        for (int i = 0; i < numVertices; i++)
        {
            if (!visitedNodes[i])
            {
                groups.resize(groups.size() + 1);
                bfs(i);
                groupCount++;
            }
        }
    }
    void findGroupsUsingDFS()
    {
        for (int i = 0; i < numVertices; i++)
        {
            if (!visitedNodes[i])
            {
                groups.resize(groups.size() + 1);
                dfs(i);
                groupCount++;
            }
        }
    }
    void displayGroups()
    {
        cout << groupCount << endl;
        for (set<int> s : groups)
        {
            cout << s.size() << endl;
            for (int vertex : s)
            {
                cout << vertex + 1 << " ";
            }
            cout << endl;
        }
    }
    void dfs(int vertex)
    {
        visitedNodes[vertex] = true;

        groups[groupCount].insert(vertex);
        for (int neighbor : adjList[vertex])
        {
            if (!visitedNodes[neighbor])
                dfs(neighbor);
        }
    }

    void readInput(istream &in)
    {
        for (int i = 0; i < numEdges; i++)
        {
            int vertex1, vertex2;
            in >> vertex1 >> vertex2;
            vertex1--;
            vertex2--;
            adjList[vertex1].push_back(vertex2);
            adjList[vertex2].push_back(vertex1);
        }
    }
    void bfs(int vertex)
    {
        queue<int> Q;
        Q.push(vertex);
        while (!Q.empty())
        {
            int current = Q.front();
            Q.pop();
            groups[groupCount].insert(current);
            for (int neighbor : adjList[current])
            {
                if (!visitedNodes[neighbor])
                {
                    visitedNodes[neighbor] = true;
                    Q.push(neighbor);
                }
            }
        }
    }
    ~Graph()
    {
        delete[] adjList;
        delete[] visitedNodes;
    }
};
