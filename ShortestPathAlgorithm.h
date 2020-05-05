//
// Created by jackh on 2020-05-03.
//
// Implement Dijkstra's algorithm to find the shortest path between two nodes.
// You must call dijkstra after initialization to run the algorithm to solve the given graph.

#ifndef DIJKSTRAALGORITHM_SHORTESTPATHALGORITHM_H
#define DIJKSTRAALGORITHM_SHORTESTPATHALGORITHM_H
#include "Graph.h"
#include <vector>
#include <queue>
#include <tuple>
#include <set>
#include <limits>

using namespace std;

class ShortestPathAlgorithm {
public:
    ShortestPathAlgorithm();
    ShortestPathAlgorithm(Graph g, int startNode, bool solve=false);
    vector<int> getShortestPath(int endNode);
    void printShortestPath(int endNode);
    double getCostOfShortestPath(int endNode);
    vector<double> getCostsOfShortestPaths();
    void runDijkstra();
    void changeStartNode(int startNode);
    void printOpenNodes(); // Inefficient print function of the openNodes priority queue used for debugging.

private:
    Graph graph;
    int startNode{};
    vector<int> shortestPathParents;
    vector<double> costsOfShortestPaths;
    set<int> closedNodes;
    bool solved{};
    const double inf = numeric_limits<double>::infinity();

    class NodeCost {
    public:
        NodeCost() : nodeCostPair({0,0}) {};
        NodeCost(int node, double cost) : nodeCostPair({node, cost}){};
        int getNode() const {
            return nodeCostPair.first;
        }
        double getCost() const {
            return nodeCostPair.second;
        }
        pair<int, double> nodeCostPair;
    };

    struct CompareNodeCost {
        bool operator() (const NodeCost &nc1, const NodeCost &nc2) {
            return nc1.nodeCostPair.second > nc2.nodeCostPair.second;
        }
    };

    priority_queue<NodeCost, vector<NodeCost>, CompareNodeCost> openNodes;
};


#endif //DIJKSTRAALGORITHM_SHORTESTPATHALGORITHM_H
