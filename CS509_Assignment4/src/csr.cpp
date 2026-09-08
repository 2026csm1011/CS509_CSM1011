#include "../headers/csr.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

CSRGraph convertToCSR(const std::string& filepath, bool isDirected) {
    CSRGraph graph;
    std::ifstream file(filepath);
    
    if (!file.is_open()) {
        std::cerr << "Error: Missing or invalid input file.\n"; // Clear error message[cite: 1]
        exit(1);
    }

    std::string line;
    if (std::getline(file, line)) {
        std::istringstream iss(line);
        iss >> graph.V >> graph.E;
    }

    graph.row_ptr.assign(graph.V + 1, 0);
    std::vector<std::vector<int>> adj_list(graph.V);

    for (int i = 0; i < graph.V; ++i) {
        if (!std::getline(file, line)) break;
        std::istringstream iss(line);
        int u, count;
        iss >> u >> count; 

        // Validate out-of-range vertex id
        if (u < 0 || u >= graph.V) {
            std::cerr << "Error: Out-of-range vertex id detected.\n";
            exit(1);
        }

        for (int j = 0; j < count; ++j) {
            int v;
            iss >> v;
            
            // Reject self loops for Vertex Coloring
            if (!isDirected && u == v) {
                std::cerr << "Error: Self-loop detected in undirected graph.\n";
                exit(1);
            }
            adj_list[u].push_back(v);
        }
    }

    // Convert internal adjacency list to flat CSR arrays
    int current_edges = 0;
    for (int i = 0; i < graph.V; ++i) {
        graph.row_ptr[i] = current_edges;
        for (int neighbor : adj_list[i]) {
            graph.col_idx.push_back(neighbor);
            current_edges++;
        }
    }
    graph.row_ptr[graph.V] = current_edges;
    
    file.close();
    return graph;
}