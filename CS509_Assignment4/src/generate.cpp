#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <random>
#include <string>

// Generates an Undirected Graph for Vertex Coloring
void generateVertexColoring(int V, int approx_E, const std::string& filename) {
    std::vector<std::set<int>> adj(V);
    int actual_E = 0;
    std::mt19937 rng(1337); // Fixed seed for reproducibility
    
    
    int target_edges = approx_E;
    
    while(actual_E < target_edges) {
        int u = rng() % V;
        int v = rng() % V;
        // No self-loops allowed in Vertex Coloring
        if (u != v && adj[u].find(v) == adj[u].end()) {
            adj[u].insert(v);
            adj[v].insert(u); // Undirected: edge in both lists
            actual_E++;
        }
    }

    std::ofstream out(filename);
    out << V << " " << actual_E << "\n";
    for (int i = 0; i < V; ++i) {
        out << i << " " << adj[i].size();
        for (int neighbor : adj[i]) {
            out << " " << neighbor;
        }
        out << "\n";
    }
    out.close();
    std::cout << "Generated " << filename << " (V=" << V << ", E=" << actual_E << ")\n";
}

// Generates a Directed Graph for PageRank
void generatePageRank(int V, int approx_E, const std::string& filename) {
    std::vector<std::vector<int>> adj(V);
    int actual_E = 0;
    std::mt19937 rng(42); 

    int edges_per_node = approx_E / V;
    if (edges_per_node == 0) edges_per_node = 1;

    for (int i = 0; i < V; ++i) {
        int out_degree = (rng() % (edges_per_node * 2)) + 1; // Ensure mostly connected
        std::set<int> seen;
        for (int d = 0; d < out_degree; ++d) {
            int target = rng() % V;
            if (seen.find(target) == seen.end()) {
                seen.insert(target);
                adj[i].push_back(target);
                actual_E++;
            }
        }
    }

    std::ofstream out(filename);
    out << V << " " << actual_E << "\n";
    for (int i = 0; i < V; ++i) {
        // List only the outgoing edges
        out << i << " " << adj[i].size();
        for (int neighbor : adj[i]) {
            out << " " << neighbor;
        }
        out << "\n";
    }
    
    // Append PageRank parameters
    out << "DAMPING 0.85\n";
    out << "TOLERANCE 0.0001\n";
    out << "MAX_ITERATIONS 100\n";
    
    out.close();
    std::cout << "Generated " << filename << " (V=" << V << ", E=" << actual_E << ")\n";
}

int main() {
    // Generate Vertex Coloring Tests (V=10, 100, 10000, 50000,100000)
    generateVertexColoring(10, 20, "tests/color_10.txt");
    generateVertexColoring(100, 300, "tests/color_100.txt");
    generateVertexColoring(10000, 30000, "tests/color_10000.txt");
    generateVertexColoring(50000, 150000, "tests/color_50000.txt");
    generateVertexColoring(100000, 200000, "tests/color_100000.txt");
    // Generate PageRank Tests (V=10, 100, 1000, 10000, 50000)
    generatePageRank(10, 25, "tests/pagerank_10.txt");
    generatePageRank(100, 250, "tests/pagerank_100.txt");
    generatePageRank(1000, 3000, "tests/pagerank_1000.txt");
    generatePageRank(10000, 30000, "tests/pagerank_10000.txt");
    generatePageRank(50000, 150000, "tests/pagerank_50000.txt");

    std::cout << "All required test files successfully generated in test/ directory!\n";
    return 0;
}