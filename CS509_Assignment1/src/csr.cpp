#include "../headers/helper.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

CSRGraph convertToCSR(const string& filename, bool isWeighted) {
    CSRGraph csr;
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file." << endl;
        return csr;
    }

    int V, E;
    file >> V >> E;
    csr.numVertices = V;
    csr.numEdges = E;
    
    csr.row_ptr.push_back(0);
    string line;
    getline(file, line); // consume newline

    for (int i = 0; i < V; ++i) {
        getline(file, line);
        if (line.empty()) { i--; continue; } // skip empty lines
        stringstream ss(line);
        int u, degree;
        ss >> u >> degree;
        
        for (int j = 0; j < degree; ++j) {
            int v;
            ss >> v;
            csr.col_idx.push_back(v);
            
            if (isWeighted) {
                int w;
                if (ss >> w) {
                    csr.values.push_back(w);
                } else {
                    csr.values.push_back(1); // default weight if missing
                }
            } else {
                csr.values.push_back(1); // Unweighted graph mein bhi default weight 1 dal dega
            }
        }
        csr.row_ptr.push_back(csr.col_idx.size());
    }
    
    file.close();
    return csr;
}