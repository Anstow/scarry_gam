#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "graph_gen.hpp"

#include <cstdlib>
#include <vector>

namespace graphs {

/*!
 * \brief The maximum number of edges that each vertex may have.
 */
constexpr unsigned max_edges_per_vertex = 4;

struct Vertex {
    unsigned id;

    VertexGen gen_info{};
};

bool operator==(Vertex const& lhs, Vertex const& rhs);

struct Edge {
    unsigned id;

    // The vertices the edge attaches
    unsigned v1;
    unsigned v2;
};

class MapGraph {
public:
    using VertexItr = std::vector<Vertex>::iterator;
    using EdgeItr = std::vector<Edge>::iterator;

private:
    std::vector<Vertex> vertices_;
    std::vector<Edge> edges_;

    GraphGen gen_info_;

    VertexItr addVertex();
    EdgeItr addEdge(VertexItr v1, VertexItr v2);

    /*!
     * \brief Gets a random vertex from the graph complete graph creates it if it doesn't exist.
     *
     * \return An iterator to the random vertex.
     */
    VertexItr randomNewVertex(VertexItr const& v);
    
public:
    MapGraph();

    VertexItr vertexFromId(unsigned vertex_id);
    EdgeItr edgeFromId(unsigned edge_id);

    VertexItr vertexBegin();
    VertexItr vertexEnd();

    EdgeItr edgeBegin();
    EdgeItr edgeEnd();

    MapGraph& process(VertexItr const& v);
    MapGraph& connect_edge(VertexItr, EdgeItr);
};

}

#endif // GRAPH_HPP
