//
// Created by jackh on 2020-05-03.
//
// Generate an undirected graph using an adjacency list.
// Nodes are simply integers from 0 to numNodes-1.
// Edges are represented as a pair<int, double> where the
// first is the node and the second is the weight of the edge.

#ifndef DIJKSTRAALGORITHM_GRAPH_H
#define DIJKSTRAALGORITHM_GRAPH_H
#include <vector>
#include <tuple>

using namespace std;

class Graph {
public:
    Graph();
    Graph(int numNodes, double density, double weightMin, double weightMax);
    int numNodes();
    int numEdges();
    bool adjacent(int from, int to);
    vector<int> getNeighbours(int node);
    void addEdge(int node1, int node2, double weight);
    void deleteEdge(int node1, int node2);
    double getEdgeValue(int node1, int node2);
    void setEdgeValue(int node1, int node2, double weight);
    friend ostream& operator<<(ostream& os, const Graph& g);
private:
    vector<vector<pair<int, double>>> adjacencyList;
};


#endif //DIJKSTRAALGORITHM_GRAPH_H
