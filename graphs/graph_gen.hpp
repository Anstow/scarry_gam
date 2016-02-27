#ifndef GRAPH_GEN_HPP
#define GRAPH_GEN_HPP

#include <random>

namespace graphs {

/*!
 * \brief The probability that a vertex has new edges added to it when it is
 * visited for any time after the first.
 */
constexpr double regen_prob = 0.1;
/*!
 * \brief The average number of edges that each vertex has
 */
constexpr double average_no_edges_per_vertex = 2.5;
/*!
 * \brief The expected number of vertices in the graph.
 */
constexpr double expected_no_vertices = 10.0;
/*!
 * \brief The maximum number of tries to find an old vertex
 */
constexpr unsigned max_tries = 10;

struct VertexGen {
    unsigned no_edges = 0;

    bool processed = false;
};

struct GraphGen {
    // For generation only: MINE KEEP OFF
    // TODO: Friend it!
    std::minstd_rand random_gen{0};

    size_t next_ver_id = 0;
    size_t next_edge_id = 0;
};

}

#endif // GRAPH_GEN_HPP
