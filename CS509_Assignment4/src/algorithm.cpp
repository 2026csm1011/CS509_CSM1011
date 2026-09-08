#include "../headers/algorithm.hpp"
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <iomanip>

// VERTEX COLORING
void vertexColoring(const CSRGraph& graph) {
    int V = graph.V;
    std::vector<int> result(V, -1); 
    std::vector<bool> available(V, false);

    // 1. Compute degrees and order vertices by non-increasing degree (Welsh-Powell)
    std::vector<int> vertices(V);
    std::iota(vertices.begin(), vertices.end(), 0);

    std::sort(vertices.begin(), vertices.end(), [&](int a, int b) {
        int deg_a = graph.row_ptr[a + 1] - graph.row_ptr[a];
        int deg_b = graph.row_ptr[b + 1] - graph.row_ptr[b];
        if (deg_a != deg_b) return deg_a > deg_b; // Non-increasing degree
        return a < b; // Tie-breaker for deterministic output
    });

    int colors_used = 0;

    // 2. Process vertices in order
    for (int u : vertices) {
        // Find used colors by neighbors
        for (int i = graph.row_ptr[u]; i < graph.row_ptr[u + 1]; ++i) {
            int neighbor = graph.col_idx[i];
            if (result[neighbor] != -1) {
                available[result[neighbor]] = true;
            }
        }

        // Assign the smallest color index not currently used by any neighbor
        int color = 0;
        while (color < V && available[color]) {
            color++;
        }
        result[u] = color;
        colors_used = std::max(colors_used, color + 1);

        // Reset available array for the next vertex
        for (int i = graph.row_ptr[u]; i < graph.row_ptr[u + 1]; ++i) {
            int neighbor = graph.col_idx[i];
            if (result[neighbor] != -1) {
                available[result[neighbor]] = false;
            }
        }
    }

    // Output formatting matching the assignment specification
    std::cout << "Algorithm: Greedy Vertex Coloring\n";
    
    // Only print full list if graph is small, prevents freezing on V=50000
    if (V <= 100) {
        std::cout << "Vertex colors:\n";
        for (int i = 0; i < V; ++i) {
            std::cout << i << " " << result[i] << "\n";
        }
    } else {
        std::cout << "Vertex colors: (Omitted from output for large graphs V > 100)\n";
    }
    
    std::cout << "Colors used: " << colors_used << "\n";
}

void runVertexColoringTask(const std::string& filepath) {
    CSRGraph graph = convertToCSR(filepath, false);
    auto start = std::chrono::high_resolution_clock::now();
    vertexColoring(graph);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    std::cout << "Execution time: " << duration.count() << " ms\n";
}

// PAGERANK
void pageRank(const CSRGraph& graph, double damping, double tolerance, int max_iterations) {
    int V = graph.V;
    std::vector<double> PR(V, 1.0 / V); // All vertices initialized with rank 1/N
    std::vector<double> next_PR(V, 0.0);
    
    int iterations = 0;
    bool converged = false;

    // Iterative update loop
    while (iterations < max_iterations) {
        std::fill(next_PR.begin(), next_PR.end(), 0.0);
        double dangling_sum = 0.0;

        // Push-based approach: iterate through outgoing edges
        for (int u = 0; u < V; ++u) {
            int out_deg = graph.row_ptr[u + 1] - graph.row_ptr[u];
            if (out_deg > 0) {
                double rank_to_distribute = PR[u] / out_deg;
                for (int i = graph.row_ptr[u]; i < graph.row_ptr[u + 1]; ++i) {
                    int v = graph.col_idx[i];
                    next_PR[v] += rank_to_distribute;
                }
            } else {
                // Outdegree 0 (dangling vertex): distribute rank evenly across all vertices
                dangling_sum += PR[u];
            }
        }

        double total_change = 0.0;
        double base_rank = (1.0 - damping) / V;
        double dangling_distribution = damping * (dangling_sum / V);
        double total_sum = 0.0;

        for (int v = 0; v < V; ++v) {
            next_PR[v] = base_rank + damping * next_PR[v] + dangling_distribution;
            total_change += std::abs(next_PR[v] - PR[v]);
            PR[v] = next_PR[v];
            total_sum += PR[v];
        }

        iterations++;

        // Check tolerance
        if (total_change <= tolerance) {
            converged = true;
            break;
        }
    }

    // Output formatting matching the assignment specification
    std::cout << "Algorithm: PageRank\n";
    std::cout << "Damping: " << damping << "\n";
    
    double sum_ranks = 0.0;
    double max_rank = -1.0;
    int top_vertex = -1;

    if (V <= 100) {
        std::cout << "Vertex ranks:\n";
    } else {
        std::cout << "Vertex ranks: (Omitted from output for large graphs V > 100)\n";
    }

    for (int i = 0; i < V; ++i) {
        if (V <= 100) {
            std::cout << i << " " << std::fixed << std::setprecision(6) << PR[i] << "\n";
        }
        sum_ranks += PR[i];
        
        // Tracking the top vertex for the table requirement
        if (PR[i] > max_rank) {
            max_rank = PR[i];
            top_vertex = i;
        }
    }
    
    std::cout << "Top Vertex: " << top_vertex << " (Rank: " << std::fixed << std::setprecision(6) << max_rank << ")\n";
    std::cout << "Sum of ranks: " << std::fixed << std::setprecision(6) << sum_ranks << "\n";
    std::cout << "Iterations: " << iterations << "\n";
    std::cout << "Converged: " << (converged ? "true" : "false") << "\n";
}

void runPageRankTask(const std::string& filepath) {
    double damping = 0.85, tolerance = 0.0001;
    int max_iter = 100;
    
    CSRGraph graph = convertToCSR(filepath, true);
    
    auto start = std::chrono::high_resolution_clock::now();
    pageRank(graph, damping, tolerance, max_iter);
    auto end = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double, std::milli> duration = end - start;
    std::cout << "Execution time: " << duration.count() << " ms\n";
}