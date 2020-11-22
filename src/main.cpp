#include <iostream>
#include "../include/GraphesOCA/Graph.hpp"

int main(int, char**) 
{
    // std::srand(time(NULL));
    // Graph edgarGraph, barbasiGraph;
    // uint nb_v, m;

    // std::cout << "Enter the # of vertices: ";
    // std::cin >> nb_v;
    // edgarGraph.generateEdgarGilbert(nb_v);
    // edgarGraph.extractTo("edgarGraph.csv");

    // std::cout << "Enter the parameter 'm' for the second graph generation: ";
    // std::cin >> m;
    // barbasiGraph.generateBarabasiAlbert(m);
    // barbasiGraph.extractTo("barbasiGraph.csv");

    Graph roadNetowkrGraph = Graph::importFrom("../database/RoadNetwork.txt", FileFormatType::ROAD_NETWORK);
    roadNetowkrGraph.dump();

    return 0;
}