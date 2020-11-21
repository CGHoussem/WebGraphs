#include <iostream>
#include "../include/GraphesOCA/Graph.hpp"

int main(int, char**) 
{
    std::srand(time(NULL));
    Graph edgarGraph, barbasiGraph;
    uint nb_v = 0, m = 0;

    std::cout << "Enter the # of vertices: ";
    std::cin >> nb_v;

    edgarGraph.generateEdgarGilbert(nb_v);

    std::cout << "Enter the parameter 'm' for the second graph generation: ";
    std::cin >> m;
    
    barbasiGraph.generateBarabasiAlbert(m);
    return 0;
}