#include <iostream>
#include "../include/GraphesOCA/Graph.cpp"

int main(int, char**) 
{
    // PARTIE I
    std::srand(time(NULL));
    Graph edgarGraph, barbasiGraph;
    uint nb_v, m;
    
    // Génération de graphe Edgar Gilbert avec 25 sommets
    edgarGraph.generateEdgarGilbert(25);
    // Affichage des informations du graphe
    edgarGraph.dump();
    // Extraction du graphe vers un fichier .csv
    edgarGraph.extractTo("edgarGraph25.csv");
    // Génération de graphe Edgar Gilbert avec 50 sommets
    edgarGraph.generateEdgarGilbert(50);
    // Affichage des informations du graphe
    edgarGraph.dump();
    // Extraction du graphe vers un fichier .csv
    edgarGraph.extractTo("edgarGraph50.csv");
    // Génération de graphe Edgar Gilbert avec 100 sommets
    edgarGraph.generateEdgarGilbert(100);
    // Affichage des informations du graphe
    edgarGraph.dump();
    // Extraction du graphe vers un fichier .csv
    edgarGraph.extractTo("edgarGraph100.csv");

    // Génération de graphe Barabasi Albert avec 25 sommets
    barbasiGraph.generateBarabasiAlbert(25);
    // Affichage des informations du graphe
    barbasiGraph.dump();
    // Extraction du graphe vers un fichier .csv
    barbasiGraph.extractTo("barbasiGraph25.csv");
    // Génération de graphe Barabasi Albert avec 50 sommets
    barbasiGraph.generateBarabasiAlbert(50);
    // Affichage des informations du graphe
    barbasiGraph.dump();
    // Extraction du graphe vers un fichier .csv
    barbasiGraph.extractTo("barbasiGraph50.csv");
    // Génération de graphe Barabasi Albert avec 100 sommets
    barbasiGraph.generateBarabasiAlbert(100);
    // Affichage des informations du graphe
    barbasiGraph.dump();
    // Extraction du graphe vers un fichier .csv
    barbasiGraph.extractTo("barbasiGraph100.csv");

    // PARTIE II
    // Importation de graphe GRAPH
    Graph roadNetwokrGraph = Graph::importFrom("../database/RoadNetwork.txt", FileFormatType::ROAD_NETWORK, true);
    std::cout << "Road Network Graph" << std::endl;
    // Affichage des informations du graphe
    roadNetwokrGraph.dump(false);
    // Extraction du graph vers un fichier .csv afin de créer du graphique
    roadNetwokrGraph.extractAxis("PlottingRoadNetwork.csv");
    
    // Importation de graphe GRAPH
    Graph facebookGraph = Graph::importFrom("../database/FacebookSites.csv", FileFormatType::FACEBOOK);
    std::cout << "Facebook Graph" << std::endl;
    // Affichage des informations du graphe
    facebookGraph.dump(false);
    // Extraction du graph vers un fichier .csv afin de créer du graphique
    roadNetwokrGraph.extractAxis("PlottingFacebook.csv");
    
    // Importation de graphe GRAPH
    Graph githubGraph = Graph::importFrom("../database/GitHub.csv", FileFormatType::GITHUB);
    std::cout << "GitHub Graph" << std::endl;
    // Affichage des informations du graphe
    githubGraph.dump(false);
    // Extraction du graph vers un fichier .csv afin de créer du graphique
    githubGraph.extractAxis("PlottingGitHub.csv");

    // Importation de graphe GRAPH
    Graph twitchGraph = Graph::importFrom("../database/twitchDE.csv", FileFormatType::TWITCH);
    std::cout << "TwitchDE Graph" << std::endl;
    // Affichage des informations du graphe
    twitchGraph.dump(false);
    // Extraction du graph vers un fichier .csv afin de créer du graphique
    twitchGraph.extractAxis("PlottingTwitch.csv");

    // Importation de graphe GRAPH
    Graph wikipedia1Graph = Graph::importFrom("../database/Wikipedia1.csv", FileFormatType::WIKIPEDIA);
    std::cout << "Wikipedia 1 Graph" << std::endl;
    // Affichage des informations du graphe
    wikipedia1Graph.dump(false);
    // Extraction du graph vers un fichier .csv afin de créer du graphique
    wikipedia1Graph.extractAxis("PlottingWikipedia1.csv");

    // Importation de graphe GRAPH
    Graph wikipedia2Graph = Graph::importFrom("../database/Wikipedia2.csv", FileFormatType::WIKIPEDIA);
    std::cout << "Wikipedia 2 Graph" << std::endl;
    // Affichage des informations du graphe
    wikipedia2Graph.dump(false);
    // Extraction du graph vers un fichier .csv afin de créer du graphique
    wikipedia2Graph.extractAxis("PlottingWikipedia2.csv");

    return 0;
}