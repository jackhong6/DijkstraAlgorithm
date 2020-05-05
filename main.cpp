#include <iostream>
#include <cmath>
#include "Graph.h"
#include "ShortestPathAlgorithm.h"

using namespace std;

double calculateAverage(vector<double> d) {
    double accumulator = 0;
    int counter = 0;
    for (auto &n : d) {
        if (!isinf(n)) {
            accumulator += n;
            counter++;
        }
    }
    return accumulator / counter;
}

int main() {
    Graph g1 = Graph(7, .2, 1.0, 10.0);
    Graph g2 = Graph(7, .4, 1.0, 10.0);
    ShortestPathAlgorithm spa1 = ShortestPathAlgorithm(g1, 0, true);
    ShortestPathAlgorithm spa2 = ShortestPathAlgorithm(g2, 0, true);
    double avgPath1 = calculateAverage(spa1.getCostsOfShortestPaths());
    double avgPath2 = calculateAverage(spa2.getCostsOfShortestPaths());
    cout << "The average path length in a random graph with 50 nodes and density 0.2 is: " << avgPath1 << endl;
    cout << "The average path length in a random graph with 50 nodes and density 0.4 is: " << avgPath2 << endl;

    cout << g1 << endl;
    cout << "Cost of shortest path to node 6: " << spa1.getCostOfShortestPath(6) << endl;
    spa1.printShortestPath(6);
    cout << endl;

    cout << g2 << endl;
    cout << "Cost of shortest path to node 3: " << spa2.getCostOfShortestPath(3) << endl;
    spa2.printShortestPath(3);
    cout << endl;
    return 0;
}
