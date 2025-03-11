#include "graph_go.hpp"
using namespace std;
int main()
{
    ifstream inputFile("input.txt");
    int vertices, edges;
    inputFile >> vertices >> edges;
    Graph graph(vertices, edges);
    graph.readInput(inputFile);
    graph.findGroupsUsingQueue();
    graph.displayGroups();
}