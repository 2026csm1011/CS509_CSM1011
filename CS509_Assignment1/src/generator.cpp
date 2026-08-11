#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <sstream>

using namespace std;

string intToString(int n) {
    stringstream ss;
    ss << n;
    return ss.str();
}

void generateGEMM(int size, string filename) {
    ofstream file(filename.c_str()); // Fixed with .c_str()
    if (!file.is_open()) return;
    file << size << " " << size << " " << size << "\n";
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            file << (rand() % 10) + 1 << " ";
        }
        file << "\n";
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            file << (rand() % 10) + 1 << " ";
        }
        file << "\n";
    }
    file.close();
}

void generateGraph(int V, string filename) {
    ofstream file(filename.c_str()); // Fixed with .c_str()
    if (!file.is_open()) return;
    int E = V * 2;
    file << V << " " << E << "\n";
    for (int i = 0; i < V; i++) {
        file << i << " 2 " << (i + 1) % V << " " << (i + 2) % V << "\n";
    }
    file << "SOURCE 0\n";
    file.close();
}

int main() {
    srand(time(0));
    generateGEMM(10, "gemm_10.txt");
    generateGEMM(100, "gemm_100.txt");
    generateGEMM(1000, "gemm_1000.txt");
    generateGEMM(5000, "gemm_5000.txt");
    
    
    int graphSizes[] = {10, 100, 10000};
    for (int i = 0; i < 3; i++) {
        int v = graphSizes[i];
        generateGraph(v, "graph_" + intToString(v) + ".txt");
    }
    cout << "Test files generated successfully!" << endl;
    return 0;
}