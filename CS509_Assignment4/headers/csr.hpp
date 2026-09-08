#ifndef CSR_H
#define CSR_H

#include <vector>
#include <string>

// Structure for the CSR representation
struct CSRGraph {
    int V; // Number of vertices
    int E; // Number of edges
    std::vector<int> row_ptr;
    std::vector<int> col_idx;
    // Values array is omitted/not required for unweighted graphs like these
};

// Converts an adjacency list file to a CSR graph
// isDirected is false for Vertex Coloring and true for PageRank
CSRGraph convertToCSR(const std::string& filepath, bool isDirected);

#endif