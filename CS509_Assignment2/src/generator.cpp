#include "../header/generator.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

int getRandomWeight() {
    int weight = (rand() % 20) + 1; 
    if (rand() % 100 < 5) weight = -weight; // 5% chance of negative edge
    return weight;
}

void generateBellmanFordGraph(int V, string filename) {
    ofstream file(filename.c_str());
    if (!file.is_open()) return;
    int E = V * 2; // Sparse edges[cite: 1]
    file << V << " " << E << "\n";
    for (int i = 0; i < V; i++) {
        file << "u" << i << " 2 " << (i + 1) % V << " " << getRandomWeight() 
             << " " << (i + 2) % V << " " << getRandomWeight() << "\n";
    }
    file << "SOURCE 0\n";
    file.close();
}

void generateFloydWarshallMatrix(int V, string filename) {
    ofstream file(filename.c_str());
    if (!file.is_open()) return;
    file << V << "\n";
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (i == j) file << "0 "; 
            else if (rand() % 100 < 20) file << "INF "; 
            else file << getRandomWeight() << " ";
        }
        file << "\n";
    }
    file.close();
}

void generateNegativeCycleTest(string filename) {
    ofstream file(filename.c_str());
    if (!file.is_open()) return;
    file << "3 3\n";
    file << "u0 1 1 5\n";     
    file << "u1 1 2 -10\n";   
    file << "u2 1 0 2\n";     
    file << "SOURCE 0\n";
    file.close();
}