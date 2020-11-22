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

    Graph roadNetowkrGraph = Graph::importFrom("../database/RoadNetwork.txt", FileFormatType::ROAD_NETWORK, true);
    std::cout << "Road Network Graph" << std::endl;
    roadNetowkrGraph.dump();

    Graph facebookGraph = Graph::importFrom("../database/FacebookSites.csv", FileFormatType::FACEBOOK);
    std::cout << "Facebook Graph" << std::endl;
    facebookGraph.dump();

    Graph githubGraph = Graph::importFrom("../database/GitHub.csv", FileFormatType::GITHUB);
    std::cout << "GitHub Graph" << std::endl;
    githubGraph.dump();

    Graph twitchGraph = Graph::importFrom("../database/twitchDE.csv", FileFormatType::TWITCH);
    std::cout << "TwitchDE Graph" << std::endl;
    twitchGraph.dump();

    Graph Wikipedia1Graph = Graph::importFrom("../database/Wikipedia1.csv", FileFormatType::WIKIPEDIA);
    std::cout << "Wikipedia 1 Graph" << std::endl;
    Wikipedia1Graph.dump();

    Graph Wikipedia2Graph = Graph::importFrom("../database/Wikipedia2.csv", FileFormatType::WIKIPEDIA);
    std::cout << "Wikipedia 2 Graph" << std::endl;
    Wikipedia2Graph.dump();

    return 0;
}