#include "Graph.hpp"
#include <fstream>
#include <sstream>
#include <regex>
#include <iostream>

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
            if (prob >= 0.5) 
            {
                edges.push_front(std::make_tuple(i, j, rand()));
                Graph::assigningNeighbours(*this, i, j);
            }
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
    edges.push_front(std::make_tuple(0, 1, rand()));
    edges.push_front(std::make_tuple(1, 2, rand()));
    edges.push_front(std::make_tuple(2, 0, rand()));
    // Assigning neighbours
    Graph::assigningNeighbours(*this, 0, 1);
    Graph::assigningNeighbours(*this, 1, 2);
    Graph::assigningNeighbours(*this, 2, 0);

    /// Running the algorithm
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
            // create a vertex
            vertices.insert(std::make_pair(vertices.size(), std::rand()));
            
            // create an edge between the created vertex and {vertex_index}
            edges.push_front(std::make_tuple(vertices.size()-1, vertex_index, rand()));
            created_edges_count++;

            // assigning neighbours
            Graph::assigningNeighbours(*this, vertices.size()-1, vertex_index);
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

std::map<std::pair<uint, uint>, int> Graph::floydWarshal()
{
    std::map<std::pair<uint, uint>, int> d;
    // d is a map of weights
    // pair(1, 2) = w
    // pair(2, 1) = w

    // initialize d
    for (const auto& v1 : vertices)
    {
        for (const auto& v2 : vertices)
        {
            auto ret = getEdgeWeight(v1.first, v2.first);
            if (ret.first)
                d[std::make_pair(v1.first, v2.first)] = ret.second;
        }
    }

    printf("initialisation complete\n");

    // floyd warshall algorithm
    for (const auto& vk : vertices)
    {
        for (const auto& v1 : vertices)
        {
            for (const auto& v2 : vertices)
            {
                auto couple = std::make_pair(v1.first, v2.first);

                d[couple] = std::min(
                    d[couple],
                    d[std::make_pair(v1.first, vk.first)] +
                    d[std::make_pair(vk.first, v2.first)]
                );
            }
        }
    }
    return d;
}

Graph Graph::importFrom(const std::string& filename, FileFormatType type, bool isDirected)
{
    Graph temp;

    std::string line;
    std::regex r;
    std::smatch m;
    u_char lines_to_skip;

    // Defining the regex pattern
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
            temp.edges.push_front(std::make_tuple(vertex1ID, vertex2ID, rand()));

            // Assigning the neighbours
            Graph::assigningNeighbours(temp, vertex1ID, vertex2ID, isDirected);
        }
        file.close();
    }
    
    return temp;
}

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

void Graph::dump() 
{
    std::cout << "# of vertices: " << getVerticesCount() << std::endl;
    std::cout << "# of edges: " << getEdgesCount() << std::endl;
    std::cout << "max degree: " << getMaxDegree() << std::endl;
    std::cout << "average degree: " << getAverageDegree() << std::endl;
    // std::cout << "diametre: " << getDiametre() << std::endl;
}

// Private Methods
void Graph::assigningNeighbours(Graph& graph, uint vertex1ID, uint vertex2ID, bool isDirected)
{
    // Assigning the neighbours
    graph.neighbours[vertex1ID].push_front(vertex2ID);
    // If the graph is not directed add parallel neighbour
    if (!isDirected)
        graph.neighbours[vertex2ID].push_front(vertex1ID);
}

uint Graph::getVerticesCount()
{
    return vertices.size();
}

uint Graph::getEdgesCount()
{
    return edges.size();
}

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

double Graph::getAverageDegree()
{
    return (double)calculateSumDegrees() / getVerticesCount();
}

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

uint Graph::getVertexDegree(uint vertexID) 
{
    return neighbours[vertexID].size();
}

uint Graph::calculateSumDegrees()
{
    return edges.size() * 2;
}

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
