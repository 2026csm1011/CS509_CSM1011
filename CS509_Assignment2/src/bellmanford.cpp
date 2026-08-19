#include "../header/algorithms.hpp"
#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;
const long long INF = 9999999999;

void run_bellman_ford_task(string filename) 
{
    ifstream file(filename.c_str());
    if (!file.is_open()) 
    {
        cout << "Error: Could not open " << filename << "\n";
        return;
    }

    int V, E;
    file >> V >> E;
    vector<vector<pair<int, long long>>> adj_list(V);
    
    for (int i = 0; i < V; ++i) 
    {
        string u_str;
        int degree;
        file >> u_str >> degree;
        for (int d = 0; d < degree; ++d) 
        {
            int neighbor;
            long long weight;
            file >> neighbor >> weight;
            adj_list[i].push_back(make_pair(neighbor, weight));
        }
    }
    string src_label;
    int source = 0;
    file >> src_label >> source; 
    file.close();

    CSRGraph csr = convert_to_csr(V, adj_list);
    vector<long long> dist(V, INF);
    dist[source] = 0;
    bool has_negative_cycle = false;

    // START TIMING 
    auto start = chrono::high_resolution_clock::now();

    for (int i = 0; i < V - 1; ++i) 
    {
        for (int u = 0; u < V; ++u) 
        {
            if (dist[u] == INF) continue;
            for (int j = csr.row_ptr[u]; j < csr.row_ptr[u + 1]; ++j) 
            {
                int v = csr.col_idx[j];
                long long weight = csr.values[j];
                if (dist[u] + weight < dist[v]) 
                {
                    dist[v] = dist[u] + weight;
                }
            }
        }
    }

    for (int u = 0; u < V; ++u) 
    {
        if (dist[u] == INF) continue;
        for (int j = csr.row_ptr[u]; j < csr.row_ptr[u + 1]; ++j) 
        {
            int v = csr.col_idx[j];
            long long weight = csr.values[j];
            if (dist[u] + weight < dist[v]) 
            {
                has_negative_cycle = true;
            }
        }
    }
    auto end = chrono::high_resolution_clock::now();
    //END TIMING

    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();

    cout << "\nAlgorithm: Bellman-Ford\nSource: " << source << "\n";
    if (has_negative_cycle) 
    {
        cout << "Negative cycle: true\n"; // 
    } 
    else 
    {
        cout << "Vertex\tDistance\n";
        for (int i = 0; i < (V > 15 ? 15 : V); ++i) 
        {
            cout << i << "\t" << (dist[i] == INF ? -1 : dist[i]) << "\n";
        }
        if (V > 15) cout << "... (output truncated for large graph)\n";
        cout << "Negative cycle: none\n";
    }
    cout << "Execution time: " << duration << " ms\n\n";
}