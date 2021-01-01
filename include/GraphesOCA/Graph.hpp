#pragma once
#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <tuple>
#include "FileFormatType.hpp"

class Graph
{
private:
    std::map<uint, int> vertices; // <vertexID, vertexValue>
    std::list<std::tuple<uint, uint, int>> edges; // <vertexID, vertexID, weight>
    std::map<uint, std::list<uint>> neighbours; // <vertexID, [vertexID1, vertexID2, ...]>

    uint getVerticesCount();
    uint getEdgesCount();
    uint getMaxDegree();
    double getAverageDegree();
    int getDiametre();

    static void assigningNeighbours(Graph& graph,  uint vertex1ID, uint vertex2ID, bool isDirected=false);

    uint calculateSumDegrees();
    uint getVertexDegree(uint vertexID);
    std::list<uint> getVertexNeighbours(uint vertexID);
    std::pair<int, bool> getEdgeWeight(uint vertexID1, uint vertexID2);
public:
    Graph();
    ~Graph();

    void generateEdgarGilbert(uint nb_s);
    void generateBarabasiAlbert(uint m);

    std::map<std::pair<uint, uint>, int> floydWarshal();

    static Graph importFrom(const std::string& filename, FileFormatType type, bool isDirected=false);
    void extractTo(const std::string& filename);
    void extractAxis(const std::string& filename);

    void dump(bool calculate_diametre=true);
};
