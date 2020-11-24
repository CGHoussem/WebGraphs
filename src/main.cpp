#include <iostream>
#include "../include/GraphesOCA/Graph.cpp"

int main(int, char**) 
{
    // PARTIE I
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

    // PARTIE II
    Graph roadNetwokrGraph = Graph::importFrom("../database/RoadNetwork.txt", FileFormatType::ROAD_NETWORK, true);
    std::cout << "Road Network Graph" << std::endl;
    // roadNetwokrGraph.dump();
    roadNetwokrGraph.extractAxis("PlottingRoadNetwork.csv");

    Graph facebookGraph = Graph::importFrom("../database/FacebookSites.csv", FileFormatType::FACEBOOK);
    std::cout << "Facebook Graph" << std::endl;
    // facebookGraph.dump();
    roadNetwokrGraph.extractAxis("PlottingFacebook.csv");

    Graph githubGraph = Graph::importFrom("../database/GitHub.csv", FileFormatType::GITHUB);
    std::cout << "GitHub Graph" << std::endl;
    // githubGraph.dump();
    githubGraph.extractAxis("PlottingGitHub.csv");
    

    Graph twitchGraph = Graph::importFrom("../database/twitchDE.csv", FileFormatType::TWITCH);
    std::cout << "TwitchDE Graph" << std::endl;
    // twitchGraph.dump();
    twitchGraph.extractAxis("PlottingTwitch.csv");


    Graph wikipedia1Graph = Graph::importFrom("../database/Wikipedia1.csv", FileFormatType::WIKIPEDIA);
    std::cout << "Wikipedia 1 Graph" << std::endl;
    // wikipedia1Graph.dump();
    wikipedia1Graph.extractAxis("PlottingWikipedia1.csv");


    Graph wikipedia2Graph = Graph::importFrom("../database/Wikipedia2.csv", FileFormatType::WIKIPEDIA);
    std::cout << "Wikipedia 2 Graph" << std::endl;
    // wikipedia2Graph.dump();
    wikipedia2Graph.extractAxis("PlottingWikipedia2.csv");

    return 0;
}