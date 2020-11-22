#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <list>

class Graph
{
private:
    std::map<uint, int> vertices; // <ID, value>
    std::list<std::pair<uint, uint>> edges; // <vertexID, vertexID>

    uint calculateSumDegrees();
    uint calculateVertexDegree(uint vertexID);
    std::list<uint> getVertexNeighbours(uint vertexID);
public:
    Graph();
    ~Graph();

    void generateEdgarGilbert(uint nb_s);
    void generateBarabasiAlbert(uint m);

    void extractTo(const std::string& filename);
};

Graph::Graph()
{
}

Graph::~Graph()
{
}

// Public Methods
void Graph::generateEdgarGilbert(uint nb_s) 
{
    // generate vertices
    for (uint i = 0; i < nb_s; i++) 
        vertices.insert(std::make_pair(i, std::rand()));

    // generate edges
    for (uint i = 0; i < nb_s; i++)
    {
        for (uint j = 0; j < nb_s; j++)
        {
            if (i == j) continue;
            double prob = ((double) std::rand() / (RAND_MAX));
            if (prob >= 0.5) edges.push_front(std::make_pair(i, j));
        }
    }

    std::cout << "A graph has been generated using Edgat Gilbert's method.\n";
}

void Graph::generateBarabasiAlbert(uint m) 
{
    /// Create the initial triangle graph
    // Create the 3 vertices
    for (uint i = 0; i < 3; i++) 
        vertices.insert(std::make_pair(i, std::rand()));
    // Create the edges between them
    edges.push_front(std::make_pair(0, 1));
    edges.push_front(std::make_pair(1, 2));
    edges.push_front(std::make_pair(2, 0));

    /// Running the algorithm
    uint created_edges_count = 0;
    uint vertex_index = 0;
    uint sum_degrees = calculateSumDegrees();
    while (created_edges_count < m)
    {
        uint degree = calculateVertexDegree(vertex_index);
        double prob = ((double) std::rand() / (RAND_MAX));
        double adding_prob = (double)degree/sum_degrees;
        if (prob <= adding_prob)
        {
            // create a vertex
            vertices.insert(std::make_pair(vertices.size(), std::rand()));
            
            // create an edge between the created vertex and {vertex_index}
            edges.push_front(std::make_pair(vertices.size()-1, vertex_index));
            created_edges_count++;
        }
        if (vertex_index++ >= vertices.size()) vertex_index = 0;
    }

    std::cout << "A graph has been generated using Barbasi-Albert's method.\n";
}

void Graph::extractTo(const std::string& filename) 
{
    // Save the list of neighbours of the vertices  
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

// Private Methods
uint Graph::calculateSumDegrees()
{
    return edges.size() * 2;
}

uint Graph::calculateVertexDegree(uint vertexID)
{
    uint sum = 0;
    for (const auto& edge : edges)
        if (edge.first == vertexID || edge.second == vertexID)
            sum ++;
    return sum;
}

std::list<uint> Graph::getVertexNeighbours(uint vertexID) 
{
    std::list<uint> neighbors;

    for (const auto& edge : edges) 
    {
        if (edge.first == vertexID)
            neighbors.push_front(edge.second);
        if (edge.second == vertexID)
            neighbors.push_front(edge.first);
    }

    return neighbors;
}