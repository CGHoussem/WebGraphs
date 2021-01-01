#include "Graph.hpp"
#include <fstream>
#include <sstream>
#include <regex>
#include <iostream>
#include <algorithm>

Graph::Graph()
{
}

Graph::~Graph()
{
}

//// Les méthodes publiques

/**
 * Cette fonction permet de générer un graphe avec l'algorithme de Edgar Gilbert.
 * 
 * @param nb_s: le nombre de sommets dans le graphe
 **/ 
void Graph::generateEdgarGilbert(uint nb_s) 
{
    // Génération des sommets
    for (uint i = 0; i < nb_s; i++) 
        vertices.insert(std::make_pair(i, std::rand()));

    // Génération des arêtes
    for (uint i = 0; i < nb_s; i++)
    {
        for (uint j = 0; j < nb_s; j++)
        {
            if (i == j) continue;
            double prob = ((double) std::rand() / (RAND_MAX));
            if (prob >= 0.5) 
            {
                edges.push_front(std::make_tuple(i, j, rand() % nb_s));
                Graph::assigningNeighbours(*this, i, j);
            }
        }
    }

    std::cout << "A graph has been generated using Edgat Gilbert's method.\n";
}

/**
 * Cette fonction permet de générer un graphe avec l'algorithme de Barabasi Albert.
 * 
 * @param m: le paramètre m
 **/ 
void Graph::generateBarabasiAlbert(uint m) 
{
    /// Création du graphe triangulaire initiale
    // Créer les 3 sommets
    for (uint i = 0; i < 3; i++) 
        vertices.insert(std::make_pair(i, std::rand()));
    // Créer les arêtes entre eux
    edges.push_front(std::make_tuple(0, 1, rand() % m));
    edges.push_front(std::make_tuple(1, 2, rand() % m));
    edges.push_front(std::make_tuple(2, 0, rand() % m));
    // Assigner les voisins
    Graph::assigningNeighbours(*this, 0, 1);
    Graph::assigningNeighbours(*this, 1, 2);
    Graph::assigningNeighbours(*this, 2, 0);

    /// Génération de l'algorithme
    uint created_edges_count = 0;
    uint vertex_index = 0;
    uint sum_degrees = calculateSumDegrees();
    while (created_edges_count < m)
    {
        uint degree = neighbours[vertex_index].size();
        double prob = ((double) std::rand() / (RAND_MAX));
        double adding_prob = (double)degree/sum_degrees;
        if (prob <= adding_prob)
        {
            // Créer un sommet
            vertices.insert(std::make_pair(vertices.size(), std::rand()));
            
            // Créer une arête entre le sommet crée et {vertex_index}
            edges.push_front(std::make_tuple(vertices.size()-1, vertex_index, rand() % m));
            created_edges_count++;

            // Assigner les voisins
            Graph::assigningNeighbours(*this, vertices.size()-1, vertex_index);
        }
        if (vertex_index++ >= vertices.size()) vertex_index = 0;
    }

    std::cout << "A graph has been generated using Barbasi-Albert's method.\n";
}

/**
 * Cette fonction permet de sauvegarder le graphe à un fichier.
 * 
 * @param filename: le nom du fichier destinataire
 **/ 
void Graph::extractTo(const std::string& filename) 
{
    // Enregistrer la liste des voisins de toutes les sommets
    std::ofstream file;
    file.open(filename);
    file << "Vertex ID; Vertex Value; Vertex Neighbours" << std::endl;
    for (const auto& v : vertices)
    {
        std::list<uint> neighbours = getVertexNeighbours(v.first);
        std::string neighboursStr;
        for (const auto& n : neighbours)
        {
            std::stringstream ss;
            ss << n << ",";
            std::string s;
            ss >> s;
            neighboursStr.append(s);
        }
        neighboursStr.pop_back();
        file << v.first << "; " << v.second << "; " << neighboursStr << std::endl;
    }
    file.close();

    std::cout << "The graph has been saved to " << filename << " successfully." << std::endl;
}

/**
 * Cette fonction permet d'exécuter l'algorithme Floyd Warshal sur le graphe.
 * 
 * @return une table de hachage ayant comme clés les paires de sommets et comme valeurs la distance entre eux
 **/ 
std::map<std::pair<uint, uint>, int> Graph::floydWarshal()
{
    // d is a map of weights
    // pair(1, 2) = w
    // pair(2, 1) = w
    std::map<std::pair<uint, uint>, int> d;

    // initialize d
    for (const auto& e : edges) {
        auto couple = std::make_pair(std::get<0>(e), std::get<1>(e));
        d[couple] = std::get<2>(e);
    }

    // floyd warshall algorithm
    for (const auto& vk : vertices)
    {
        for (const auto e : edges) {
            auto couple = std::make_pair(std::get<0>(e), std::get<1>(e));

            if (d.find(std::make_pair(std::get<0>(e), vk.first)) == d.end()) continue;
            if (d.find(std::make_pair(vk.first, std::get<1>(e))) == d.end()) continue;
            d[couple] = std::min(
                d[couple],
                d[std::make_pair(std::get<0>(e), vk.first)] +
                d[std::make_pair(vk.first, std::get<1>(e))]
            );
        }
    }

    return d;
}

/**
 * Cette fonction permet de charger un graphe depuis un fichier.
 * 
 * @param filename: Le nom du fichier
 * @param type: Le type du graphe chargé (Facebook/TwitchDE/GitHub/..)
 * @param isDirected: Si le graphe chargé est orienté ou pas
 * 
 * @return Un graphe
 **/ 
Graph Graph::importFrom(const std::string& filename, FileFormatType type, bool isDirected)
{
    Graph temp;

    std::string line;
    std::regex r;
    std::smatch m;
    u_char lines_to_skip;

    // Définir le pattern regex
    switch (type)
    {
    case FileFormatType::ROAD_NETWORK:
        r = "(.*)\t(.*)";
        lines_to_skip = 4;
        break;
    default:
        r = "(.*),(.*)";
        lines_to_skip = 1;
        break;
    }

    std::ifstream file(filename);
    if (file.is_open())
    {
        // Skipping the header lines
        uint i = 0;
        while (i++ < lines_to_skip) getline(file, line);

        // Extracting vertices & edges
        while (getline(file, line))
        {
            // Getting the vertices ids with a regex search
            std::regex_search(line, m, r);
            uint vertex1ID = std::stoi(m[1].str());
            uint vertex2ID = std::stoi(m[2].str());

            // Adding the vertices to the vertices map
            temp.vertices.insert(std::make_pair(vertex1ID, -1));
            temp.vertices.insert(std::make_pair(vertex2ID, -1));

            // Adding the edge connection the extracted vertices
            temp.edges.push_front(std::make_tuple(vertex1ID, vertex2ID, rand() % 100));

            // Assigning the neighbours
            Graph::assigningNeighbours(temp, vertex1ID, vertex2ID, isDirected);
        }
        file.close();
    }
    
    return temp;
}

/**
 * Cette fonction permet d'enregister en un fichier les degrees et leurs occurences du graphe.
 * 
 * @param filename: Le nom du fichier destinataire
 **/ 
void Graph::extractAxis(const std::string& filename)
{
    // x axis : # of neighbours
    // y axis : occurrence frequency

    // Counting (# of neighbours) occurences
    std::map<uint, uint> frequencies;
    for (const auto& v : vertices)
    {
        uint deg = getVertexDegree(v.first);
        if (frequencies.find(deg) != frequencies.end()) 
            frequencies[deg]++;
        else
            frequencies[deg] = 1;
    }

    // Extracting data to a csv file (format: x axis, y axis)
    std::ofstream file;
    file.open(filename);
    file << "Degree;Occurrence" << std::endl;
    for (const auto& f : frequencies)
    {
        uint degree = f.first;
        uint occ = f.second;

        file << degree << ";" << occ << std::endl;
    }
    file.close();

    std::cout << "The graph plotting axis has been extracted to " << filename << " successfully." << std::endl;

}

/**
 * Cette fonction permet d'afficher les informations du graphe.
 **/ 
void Graph::dump(bool calculate_diametre) 
{
    std::cout << "# of vertices: " << getVerticesCount() << std::endl;
    std::cout << "# of edges: " << getEdgesCount() << std::endl;
    std::cout << "max degree: " << getMaxDegree() << std::endl;
    std::cout << "average degree: " << getAverageDegree() << std::endl;
    if (calculate_diametre)
        std::cout << "diametre: " << getDiametre() << std::endl;
}

/// Méthodes privés

/**
 * Cette fonction permet d'assigner les voisins d'un graphe.
 * 
 * @param graph: L'adresse du graphe.
 * @param vertex1ID: L'identifiant du premier sommet
 * @param vertex2ID: L'identifiant du deuxiéme sommet
 * @param isDirected: Si le graphe est orienté ou pas
 **/ 
void Graph::assigningNeighbours(Graph& graph, uint vertex1ID, uint vertex2ID, bool isDirected)
{
    // Assigning the neighbours
    graph.neighbours[vertex1ID].push_front(vertex2ID);
    // If the graph is not directed add parallel neighbour
    if (!isDirected)
        graph.neighbours[vertex2ID].push_front(vertex1ID);
}

/**
 * Cette fonction permet de retourner le nombre de sommets
 * 
 * @return Le nombre de sommets
 **/ 
uint Graph::getVerticesCount()
{
    return vertices.size();
}

/**
 * Cette fonction permet de retourner le nombre d'arêtes
 * 
 * @return Le nombre de sommets
 **/ 
uint Graph::getEdgesCount()
{
    return edges.size();
}

/**
 * Cette fonction permet de calculer et retourner le maximum des degrés
 * 
 * @return Le maximum des degrés
 **/ 
uint Graph::getMaxDegree()
{
    uint max = 0;
    for (const auto& v : vertices)
    {
        uint deg = getVertexDegree(v.first);
        if (deg > max) max = deg;
    }
    return max;
}

/**
 * Cette fonction permet de calculer et retourner la moyenne des degrés
 * 
 * @return La moyenne des degrés
 **/ 
double Graph::getAverageDegree()
{
    return (double)calculateSumDegrees() / getVerticesCount();
}

/**
 * Cette fonction permet de calculer et retourner le diamètre du graphe.
 * 
 * @return Le diamètre du graphe
 **/ 
int Graph::getDiametre()
{
    int diametre = 0;
    std::map<std::pair<uint, uint>, int> d = floydWarshal();
    for (std::pair<std::pair<uint, uint>, int> element : d) {
        uint distance = element.second;
        if (diametre < distance)
            diametre = distance;
    }
    return diametre;
}

/**
 * Cette fonction permet de retourner le degré d'un sommet donnée.
 * 
 * @param vertexID: L'identifiant du sommet
 * 
 * @return Le degré du sommet donnée
 **/ 
uint Graph::getVertexDegree(uint vertexID) 
{
    return neighbours[vertexID].size();
}

/**
 * Cette fonction permet de calculer et retourner la somme de dégrés
 * 
 * @return La somme de degrés
 **/ 
uint Graph::calculateSumDegrees()
{
    return edges.size() * 2;
}

/**
 * Cette fonction permet de retourner les sommets voisins d'un sommet donné
 * 
 * @param vertexID: L'identifiant du sommet
 * 
 * @return Liste des identifiants de sommets voisins
 **/ 
std::list<uint> Graph::getVertexNeighbours(uint vertexID) 
{
    std::list<uint> neighbors;

    for (const auto& edge : edges) 
    {
        if (std::get<0>(edge) == vertexID)
            neighbors.push_front(std::get<1>(edge));
        if (std::get<1>(edge) == vertexID)
            neighbors.push_front(std::get<0>(edge));
    }

    return neighbors;
}

/**
 * Cette fonction permet de retourner le poids de l'arềte entre deux sommets donnés.
 * 
 * @param vertexID1: L'identifiant du 1er sommet
 * @param vertexID2: L'identifiant du 2eme sommet
 * 
 * @return Un pair contenant le poids de l'arête entre ces deux sommets et si l'arête existe ou pas.
 **/ 
std::pair<int, bool> Graph::getEdgeWeight(uint vertexID1, uint vertexID2)
{
    for (const auto& edge : edges)
    {
        if (std::get<0>(edge) == vertexID1 &&
            std::get<1>(edge) == vertexID2)
            return std::make_pair(std::get<2>(edge), true);
    }

    return std::make_pair(-1, false);
}
