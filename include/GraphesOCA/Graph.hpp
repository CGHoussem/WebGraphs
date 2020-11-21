#pragma once
#include <iostream>
#include <map>
#include <list>

class Graph
{
private:
    std::map<uint, int> vertices; // <ID, value>
    std::list<std::pair<uint, uint>> edges; // <vertexID, vertexID>

    uint calculateSumDegrees();
    uint calculateVertexDegree(uint vertexID);
public:
    Graph();
    ~Graph();

    void generateEdgarGilbert(uint nb_s);
    void generateBarabasiAlbert(uint m);

    void printAll();
};

Graph::Graph()
{
}

Graph::~Graph()
{
}

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

void Graph::printAll()
{
    uint c_tabs = 0;
    std::cout << "Edges\n";
    for (const auto& v : edges)
    {
        std::cout << v.first << "+" << v.second << "\t";
        if (c_tabs++ >= 4)
        {
            std::cout << std::endl;
            c_tabs = 0;
        }
    }
}
