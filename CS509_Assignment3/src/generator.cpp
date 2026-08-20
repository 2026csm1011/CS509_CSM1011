#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <set>
#include <string>

using namespace std;

struct Edge 
{
    int v, weight;
};

void generateConnectedGraph(int V, int E, const string& filename) 
{
    if (E < V - 1) 
    {
        cerr << "Error: E must be >= V - 1 for a connected graph.\n";
        return;
    }

    vector<vector<Edge>> adj_list(V);
    set<pair<int, int>> edge_tracker;

    srand(time(NULL));

    // Ensure connectivity
    for (int i = 1; i < V; ++i) 
    {
        int u = rand() % i; 
        int v = i;
        int w = (rand() % 100) + 1; 

        adj_list[u].push_back({v, w});
        adj_list[v].push_back({u, w});
        edge_tracker.insert({min(u, v), max(u, v)});
    }

    // Add remaining random edges
    int edges_added = V - 1;
    while (edges_added < E) 
    {
        int u = rand() % V;
        int v = rand() % V;
        if (u == v) continue;

        int min_node = min(u, v);
        int max_node = max(u, v);

        if (edge_tracker.find({min_node, max_node}) == edge_tracker.end()) 
        {
            int w = (rand() % 100) + 1;
            adj_list[u].push_back({v, w});
            adj_list[v].push_back({u, w});
            edge_tracker.insert({min_node, max_node});
            edges_added++;
        }
    }

    // Write to file
    ofstream outfile(filename);
    outfile << V << " " << E << "\n";

    for (int u = 0; u < V; ++u) 
    {
        outfile << u << " " << adj_list[u].size();
        for (const auto& edge : adj_list[u]) 
        {
            outfile << " " << edge.v << " " << edge.weight;
        }
        outfile << "\n";
    }

    outfile.close();
    cout << "Generated: " << filename << " (V = " << V << ", E = " << E << ")\n";
}

int main(int argc, char* argv[]) 
{
    
    if (argc == 1) {
        cout << "Auto-generating test files...\n";
        
        vector<pair<int, int>> required_sizes = 
        {
            {10, 30},
            {100, 300},
            {10000, 30000},
            {50000, 150000},
            {100000, 300000}
        };

        for (const auto& size : required_sizes) 
        {
            int V = size.first;
            int E = size.second;
            string filename = "mst_" + to_string(V) + ".txt";
            generateConnectedGraph(V, E, filename);
        }
       
        return 0;
    }

   
    if (argc == 4) 
    {
        int V = stoi(argv[1]);
        int E = stoi(argv[2]);
        string filename = argv[3];
        generateConnectedGraph(V, E, filename);
        return 0;
    }

    // INVALID USAGE
    cout << "Usage Options:\n";
    cout << "  Auto-generate all: ./graph_generator\n";
    cout << "  Generate custom:   ./graph_generator <V> <E> <output_file.txt>\n";
    return 1;
}