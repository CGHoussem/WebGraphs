#pragma once
#include <iostream>
#include <map>
#include <list>
#include "FileFormatType.hpp"

class Graph
{
private:
    std::map<uint, int> vertices; // <vertexID, vertexValue>
    std::list<std::pair<uint, uint>> edges; // <vertexID, vertexID>
    std::map<uint, std::list<uint>> neighbours; // <vertexID, [vertexID1, vertexID2, ...]>

    uint getVerticesCount();
    uint getEdgesCount();
    uint getMaxDegree();
    double getAverageDegree();

    static void assigningNeighbours(Graph& graph,  uint vertex1ID, uint vertex2ID, bool isDirected=false);

    uint calculateSumDegrees();
    uint calculateVertexDegree(uint vertexID);
    std::list<uint> getVertexNeighbours(uint vertexID);
public:
    Graph();
    ~Graph();

    void generateEdgarGilbert(uint nb_s);
    void generateBarabasiAlbert(uint m);

    static Graph importFrom(const std::string& filename, FileFormatType type, bool isDirected=false);
    void extractTo(const std::string& filename);

    void dump();
};
