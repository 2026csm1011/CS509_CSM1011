#include "../header/csr.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

bool ConvertToCSR(const string& filename, CSRGraph& graph) {
    ifstream infile(filename);
    if (!infile.is_open()) {
        cerr << "Error: Could not open input file " << filename << "\n";
        return false;
    }

    if (!(infile >> graph.V >> graph.E)) {
        cerr << "Error: Invalid graph dimensions.\n";
        return false;
    }

    // Temporary adjacency list to build CSR
    vector<vector<pair<int, int>>> adjacency_list(graph.V);

    string line;
    getline(infile, line); // consume newline after V E
    
    for (int i = 0; i < graph.V; ++i) {
        getline(infile, line);
        if (line.empty()) continue;
        
        stringstream ss(line);
        int current_node, degree;
        ss >> current_node >> degree;
        
        for (int j = 0; j < degree; ++j) {
            int neighbor_node, edge_weight;
            ss >> neighbor_node >> edge_weight;
            adjacency_list[current_node].push_back({neighbor_node, edge_weight});
        }
    }

    // Convert adjacency list to CSR
    graph.row_ptr.assign(graph.V + 1, 0);
    graph.col_idx.clear();
    graph.values.clear();

    int current_edges = 0;
    for (int u = 0; u < graph.V; ++u) {
        graph.row_ptr[u] = current_edges;
        for (const auto& edge : adjacency_list[u]) {
            graph.col_idx.push_back(edge.first);
            graph.values.push_back(edge.second);
            current_edges++;
        }
    }
    graph.row_ptr[graph.V] = current_edges;

    infile.close();
    return true;
}