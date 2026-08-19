#include "../header/algorithm.hpp"
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <chrono> 

using namespace std;
using namespace std::chrono; 

struct Edge 
{
    int u, v, w;
    bool operator<(const Edge& o) const { return w < o.w; }
    bool operator>(const Edge& o) const { return w > o.w; }
};

// Union-Find to prevent cycles
class UnionFind 
{
    vector<int> parent, rank;
public:
    UnionFind(int n) : parent(n), rank(n, 0) 
    {
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    int find(int i)
    { 
        return (parent[i] == i) ? i : (parent[i] = find(parent[i])); 
    }
    bool unite(int i, int j) 
    {
        int root_i = find(i), root_j = find(j);
        if (root_i == root_j) return false;
        if (rank[root_i] < rank[root_j]) parent[root_i] = root_j;
        else if (rank[root_i] > rank[root_j]) parent[root_j] = root_i;
        else 
        { 
            parent[root_j] = root_i; rank[root_i]++; 
        }
        return true;
    }
};


void Kruskal(const CSRGraph& graph) 
{
    auto start_time = high_resolution_clock::now(); 

    vector<Edge> edges;
    for (int u = 0; u < graph.V; ++u) 
    {
        for (int i = graph.row_ptr[u]; i < graph.row_ptr[u + 1]; ++i) 
        {
            if (u < graph.col_idx[i]) edges.push_back({u, graph.col_idx[i], graph.values[i]});
        }
    }
    sort(edges.begin(), edges.end());

    UnionFind uf(graph.V);
    long long total_weight = 0;
    for (const auto& e : edges) 
    {
        if (uf.unite(e.u, e.v)) 
        {
            total_weight += e.w;
        }
    }

    auto end_time = high_resolution_clock::now(); 
    auto duration_ms = duration_cast<milliseconds>(end_time - start_time).count(); 

    cout << "Kruskal Weight: " << total_weight << "\n";
    cout << "Kruskal Time: " << duration_ms << " ms\n\n";
}


void Prim(const CSRGraph& graph) 
{
    auto start_time = high_resolution_clock::now(); 

    vector<bool> visited(graph.V, false);
    priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
    long long total_weight = 0;

    visited[0] = true;
    for (int i = graph.row_ptr[0]; i < graph.row_ptr[0 + 1]; ++i) pq.push({0, graph.col_idx[i], graph.values[i]});

    while (!pq.empty()) 
    {
        Edge e = pq.top(); pq.pop();
        if (visited[e.v]) continue;

        visited[e.v] = true;
        total_weight += e.w;

        for (int i = graph.row_ptr[e.v]; i < graph.row_ptr[e.v + 1]; ++i) 
        {
            if (!visited[graph.col_idx[i]]) pq.push({e.v, graph.col_idx[i], graph.values[i]});
        }
    }

    auto end_time = high_resolution_clock::now(); 
    auto duration_ms = duration_cast<milliseconds>(end_time - start_time).count(); 

    cout << "Prim Weight: " << total_weight << "\n";
    cout << "Prim Time: " << duration_ms << " ms\n\n";
}