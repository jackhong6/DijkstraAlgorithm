//
// Created by jackh on 2020-05-03.
//

#include "Graph.h"
#include <random>
#include <tuple>
#include <chrono>
#include <iostream>
#include <iomanip>

using namespace std;

Graph::Graph() : adjacencyList(0){}

Graph::Graph(int numNodes, double density, double weightMin, double weightMax) : adjacencyList(numNodes) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    uniform_real_distribution<double> probDistribution(0.0, 1.0);
    uniform_real_distribution<double> weightDistribution(weightMin, weightMax);

    // loop through every possible edge
    for (int i=0; i<numNodes-1; ++i) {
        for (int j=i+1; j<numNodes; ++j) {
            if (probDistribution(generator) < density) {
                double weight = weightDistribution(generator);
                adjacencyList[i].emplace_back(make_pair(j, weight));
                adjacencyList[j].emplace_back(make_pair(i, weight));
            }
        }
    }

}

int Graph::numEdges() {
    int accumulator = 0;
    for (auto &edgeList : adjacencyList) {
        accumulator += edgeList.size();
    }

    return accumulator / 2; // the for loop double counts each edge
}

int Graph::numNodes() {
    return adjacencyList.size();
}

bool Graph::adjacent(int from, int to) {
    if (from >= numNodes() || to >=numNodes()) return false;
    bool adj = false;
    vector<pair<int, double>> nodeList = adjacencyList[from];
    for  (auto &node_pair : nodeList) {
        if (node_pair.first == to) adj = true;
    }
    return adj;
}

vector<int> Graph::getNeighbours(int node) {
    if (node >= numNodes()) return vector<int>(0);
    vector<int> neighbours;
    for (auto & n : adjacencyList[node]) {
        neighbours.push_back(n.first);
    }
    return neighbours;
}

void Graph::addEdge(int node1, int node2, double weight) {
    if (node1 >= numNodes() || node2 >=numNodes()) return;
    adjacencyList[node1].push_back(make_pair(node2, weight));
    adjacencyList[node2].push_back(make_pair(node1, weight));
}

void Graph::deleteEdge(int node1, int node2) {
    if (node1 >= numNodes() || node2 >=numNodes()) return;

    int counter = 0;
    for (auto &n : adjacencyList[node1]) {
        if (n.first == node2) adjacencyList[node1].erase(adjacencyList[node1].begin() + counter);
        counter++;
    }

    counter = 0;
    for (auto &n : adjacencyList[node2]) {
        if (n.first == node1) adjacencyList[node2].erase(adjacencyList[node2].begin() + counter);
        counter++;
    }
}

double Graph::getEdgeValue(int node1, int node2) {
    if (node1 >= numNodes() || node2 >=numNodes()) return 0;

    for (auto &n : adjacencyList[node1]) {
        if (n.first == node2) return n.second;
    }
    return 0;
}

void Graph::setEdgeValue(int node1, int node2, double weight) {
    if (node1 >= numNodes() || node2 >=numNodes()) return;

    for (auto &n : adjacencyList[node1]) {
        if (n.first == node2) n.second = weight;
    }

    for (auto &n : adjacencyList[node2]) {
        if (n.first == node1) n.second = weight;
    }

}

ostream &operator<<(ostream &out, const Graph &g) {
    out << std::fixed;
    out << std::setprecision(2);
    int counter = 0;
    for (auto & nodeList : g.adjacencyList) {
        out << counter;
        for (auto & node : nodeList) {
            out << " -(" << node.second << ")-> "<< node.first;
        }
        out << endl;
        counter++;
    }
    return out;
}