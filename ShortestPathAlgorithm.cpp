//
// Created by jackh on 2020-05-03.
//

#include "ShortestPathAlgorithm.h"
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

ShortestPathAlgorithm::ShortestPathAlgorithm() = default;

// Initialize the priority queue of openNodes to set the cost of reaching of the start node to zero;
// the cost of all the other nodes is set to infinity. Dijkstra's algorithm is run if the solve variable
// is set to true. Otherwise you must call the runDijkstra() method first for the other get methods to return
// the correct shortest paths.
ShortestPathAlgorithm::ShortestPathAlgorithm(Graph g, int startNode, bool solve)
: graph(g), startNode(startNode), solved(false), closedNodes(), shortestPathParents(g.numNodes(), -1){
    costsOfShortestPaths = vector<double> (g.numNodes(), inf);
    costsOfShortestPaths[startNode] = 0;
    openNodes.push(NodeCost(startNode, 0));
    for (int i=0; i<g.numNodes(); ++i) {
        if (i != startNode) openNodes.push(NodeCost(i, inf));
    }
    if (solve) runDijkstra();
}

vector<int> ShortestPathAlgorithm::getShortestPath(int endNode) {
    if (!solved) runDijkstra();
    if (costsOfShortestPaths[endNode] == inf) return vector<int>(0);
    vector<int> shortestPath;
    int currentNode = endNode;
    shortestPath.push_back(currentNode);
    while (currentNode != startNode) {
        shortestPath.push_back(shortestPathParents[currentNode]);
        currentNode = shortestPathParents[currentNode];
    }
    reverse(shortestPath.begin(), shortestPath.end());
    return shortestPath;
}

double ShortestPathAlgorithm::getCostOfShortestPath(int endNode) {
    if (!solved) runDijkstra();
    return costsOfShortestPaths[endNode];
}

void ShortestPathAlgorithm::runDijkstra() {
    while (!isinf(openNodes.top().getCost())) {
        NodeCost nc = openNodes.top();
        int u = nc.getNode();
        if (closedNodes.count(u)) {
            openNodes.pop();
            continue;
        }
        closedNodes.insert(u);
        vector<int> neighbours = graph.getNeighbours(u);
        for (auto &v : neighbours) {
            double costFromU = costsOfShortestPaths[u] + graph.getEdgeValue(u, v);
            if (!closedNodes.count(v) && costsOfShortestPaths[v] > costFromU) {
                openNodes.push(NodeCost(v, costFromU));
                costsOfShortestPaths[v] = costFromU;
                shortestPathParents[v] = u;
            }
        }
        openNodes.pop();
    }
    solved = true;
}

void ShortestPathAlgorithm::printOpenNodes() {
    auto *openNodesCopy = new priority_queue<NodeCost, vector<NodeCost>, CompareNodeCost> (openNodes);
    while (!openNodesCopy->empty()) {
        NodeCost nc = openNodesCopy->top();
        cout << "( " << nc.getNode() << ", " << nc.getCost() << ")" << endl;
        openNodesCopy->pop();
    }
}

vector<double> ShortestPathAlgorithm::getCostsOfShortestPaths() {
    if (!solved) runDijkstra();
    return costsOfShortestPaths;
}

void ShortestPathAlgorithm::printShortestPath(int endNode) {
    vector<int> shortestPath = getShortestPath(endNode);
    for (auto &node : shortestPath) {
        cout << node << " --> ";
    }
    cout << "END" << endl;
}

void ShortestPathAlgorithm::changeStartNode(int sNode) {
    this->startNode = sNode;
    solved = false;
}

