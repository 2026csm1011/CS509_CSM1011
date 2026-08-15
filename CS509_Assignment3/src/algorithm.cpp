#include "../header/algorithm.hpp"
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;
// Data Structures
struct Edge 
{
    int source_node;
    int target_node;
    int edge_weight;
    
    bool operator<(const Edge& other_edge) const 
    {
        return edge_weight < other_edge.edge_weight;
    }
};

class UnionFind 
{
private:
    vector<int> parent_node;
    vector<int> tree_depth;

public:
    UnionFind(int total_nodes) 
    {
        parent_node.resize(total_nodes);
        tree_depth.resize(total_nodes, 0);
        for (int i = 0; i < total_nodes; i++) 
        {
            parent_node[i] = i;
        }
    }
    
    int find_root(int node) 
    {
        if (parent_node[node] == node) return node;
        return parent_node[node] = find_root(parent_node[node]); 
    }
    
    bool connect_nodes(int node_a, int node_b) 
    {
        int root_a = find_root(node_a);
        int root_b = find_root(node_b);
        
        if (root_a != root_b) {
            if (tree_depth[root_a] < tree_depth[root_b]) 
            {
                parent_node[root_a] = root_b;
            } else if (tree_depth[root_a] > tree_depth[root_b]) 
            {
                parent_node[root_b] = root_a;
            } 
            else 
            {
                parent_node[root_b] = root_a;
                tree_depth[root_a]++;
            }
            return true;
        }
        return false;
    }
};

// Algorithms

void Kruskal(const CSRGraph& graph) 
{
    auto start_time = high_resolution_clock::now();

    vector<Edge> all_edges;
    
    for (int current_node = 0; current_node < graph.V; ++current_node) 
    {
        int neighbor_start = graph.row_ptr[current_node];
        int neighbor_end = graph.row_ptr[current_node + 1];
        
        for (int i = neighbor_start; i < neighbor_end; ++i) 
        {
            int neighbor_node = graph.col_idx[i];
            int weight = graph.values[i];
            
            if (current_node < neighbor_node) 
            { 
                all_edges.push_back({current_node, neighbor_node, weight});
            }
        }
    }
    
    sort(all_edges.begin(), all_edges.end());

    UnionFind network_manager(graph.V);
    vector<Edge> final_tree_edges;
    long long total_minimum_weight = 0;

    for (const auto& current_edge : all_edges) 
    {
        if (network_manager.connect_nodes(current_edge.source_node, current_edge.target_node)) 
        {
            final_tree_edges.push_back(current_edge);
            total_minimum_weight += current_edge.edge_weight;
            
            if (final_tree_edges.size() == graph.V - 1) break;
        }
    }

    auto end_time = high_resolution_clock::now();
    auto duration_ms = duration_cast<milliseconds>(end_time - start_time).count();

    cout << "Algorithm: Kruskal's MST\n";
    cout << "MST edges:\n";
    
    int print_limit = 25;
    for (int i = 0; i < final_tree_edges.size(); ++i) 
    {
        if (i < print_limit) 
        {
            cout << final_tree_edges[i].source_node << " " << final_tree_edges[i].target_node << " " << final_tree_edges[i].edge_weight << "\n";
        } 
        else 
        {
            cout << "... (and " << final_tree_edges.size() - print_limit << " more edges omitted to keep terminal clean)\n";
            break; 
        }
    }
    
    cout << "Total MST weight: " << total_minimum_weight << "\n";
    cout << "Execution time: " << duration_ms << " ms\n\n";
}

void Prim(const CSRGraph& graph) 
{
    auto start_time = high_resolution_clock::now();

    vector<bool> is_visited(graph.V, false);
    vector<Edge> final_tree_edges;
    long long total_minimum_weight = 0;
    
    typedef pair<int, pair<int, int>> QueueItem;
    priority_queue<QueueItem, vector<QueueItem>, greater<QueueItem>> minimum_edge_queue;

    int starting_node = 0;
    is_visited[starting_node] = true;
    
    int neighbor_start = graph.row_ptr[starting_node];
    int neighbor_end = graph.row_ptr[starting_node + 1];
    
    for (int i = neighbor_start; i < neighbor_end; ++i) 
    {
        int neighbor_node = graph.col_idx[i];
        int weight = graph.values[i];
        minimum_edge_queue.push({weight, {starting_node, neighbor_node}});
    }

    while (!minimum_edge_queue.empty() && final_tree_edges.size() < graph.V - 1) 
    {
        auto best_available_edge = minimum_edge_queue.top();
        minimum_edge_queue.pop();

        int edge_weight = best_available_edge.first;
        int source_node = best_available_edge.second.first;
        int target_node = best_available_edge.second.second;

        if (is_visited[target_node]) continue;

        is_visited[target_node] = true;
        final_tree_edges.push_back({source_node, target_node, edge_weight});
        total_minimum_weight += edge_weight;

        int next_neighbor_start = graph.row_ptr[target_node];
        int next_neighbor_end = graph.row_ptr[target_node + 1];
        
        for (int i = next_neighbor_start; i < next_neighbor_end; ++i) 
        {
            int new_neighbor = graph.col_idx[i];
            int new_weight = graph.values[i];
            
            if (!is_visited[new_neighbor]) 
            {
                minimum_edge_queue.push({new_weight, {target_node, new_neighbor}});
            }
        }
    }

    auto end_time = high_resolution_clock::now();
    auto duration_ms = duration_cast<milliseconds>(end_time - start_time).count();

    cout << "Algorithm: Prim's MST\n";
    cout << "MST edges:\n";
    
    int print_limit = 25;
    for (int i = 0; i < final_tree_edges.size(); ++i) 
    {
        if (i < print_limit) 
        {
            cout << final_tree_edges[i].source_node << " " << final_tree_edges[i].target_node << " " << final_tree_edges[i].edge_weight << "\n";
        } 
        else 
        {
            cout << "... (and " << final_tree_edges.size() - print_limit << " more edges omitted to keep terminal clean)\n";
            break; 
        }
    }
    
    cout << "Total MST weight: " << total_minimum_weight << "\n";
    cout << "Execution time: " << duration_ms << " ms\n\n";
}