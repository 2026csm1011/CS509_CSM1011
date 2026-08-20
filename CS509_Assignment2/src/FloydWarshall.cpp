#include "../header/algorithms.hpp"
#include <iostream>
#include <fstream>
#include <chrono>
#include <string>

using namespace std;
const long long INF = 9999999999;

void run_floyd_warshall_task(string filename) 
{
    ifstream file(filename.c_str());
    if (!file.is_open()) 
    {
        cout << "Error: Could not open " << filename << "\n";
        return;
    }

    int V;
    file >> V;
    vector<vector<long long>> dist(V, vector<long long>(V));
    for (int i = 0; i < V; ++i) 
    {
        for (int j = 0; j < V; ++j) 
        {
            string val;
            file >> val;
            if (val == "INF") dist[i][j] = INF; // Handles INF tokens
            else dist[i][j] = stoll(val);
        }
    }
    file.close();

    bool has_negative_cycle = false;

    // START TIMING
    auto start = chrono::high_resolution_clock::now();
    
    for (int k = 0; k < V; ++k) 
    {
        for (int i = 0; i < V; ++i) 
        {
            for (int j = 0; j < V; ++j) 
            {
                if (dist[i][k] != INF && dist[k][j] != INF) 
                {
                    if (dist[i][k] + dist[k][j] < dist[i][j]) 
                    {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
    }
    
    // Check diagonal for negative cycles
    for (int i = 0; i < V; ++i) {
        if (dist[i][i] < 0) has_negative_cycle = true; 
    }
    auto end = chrono::high_resolution_clock::now();
    // END TIMING

    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();

    cout << "\nAlgorithm: Floyd-Warshall\n";
    if (has_negative_cycle) 
    {
        cout << "Negative cycle: true\n"; // Omits matrix if cycle found
    } 
    else 
    {
        cout << "Distance matrix:\n";
        int printLimit = (V > 10 ? 10 : V); 
        for (int i = 0; i < printLimit; ++i) {
            for (int j = 0; j < printLimit; ++j) 
            {
                if (dist[i][j] == INF) cout << "INF\t";
                else cout << dist[i][j] << "\t";
            }
            cout << "\n";
        }
        if (V > 10) cout << "... (output truncated for large graph)\n";
        cout << "Negative cycle: none\n";
    }
    cout << "Execution time: " << duration << " ms\n\n";
}