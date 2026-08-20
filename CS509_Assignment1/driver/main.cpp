#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <string>
#include "../headers/helper.hpp"

using namespace std;

int main(int argc, char* argv[]) 
{
    if (argc < 3) 
    {
        cout << "Error: Missing arguments." << endl;
        cout << "Usage: ./main <algorithm> <filename.txt>" << endl;
        return 1;
    }

    string algo = argv[1];
    string filename = argv[2];

    if (algo == "gemm") 
    {
        ifstream file(filename.c_str());
        if (!file.is_open()) 
        {
            cout << "Error: Invalid or missing input file." << endl;
            return 1;
        }

        int M, K, N;
        file >> M >> K >> N;

        vector<vector<int>> A(M, vector<int>(K));
        for (int i = 0; i < M; i++) 
        {
            for (int j = 0; j < K; j++) file >> A[i][j];
        }

        vector<vector<int>> B(K, vector<int>(N));
        for (int i = 0; i < K; i++) 
        {
            for (int j = 0; j < N; j++) file >> B[i][j];
        }
        file.close();

        vector<vector<int>> C_simple(M, vector<int>(N, 0));
        vector<vector<int>> C_blocking(M, vector<int>(N, 0));

        // Timing Simple GEMM
        auto start1 = chrono::high_resolution_clock::now();
        runSimpleGEMM(M, K, N, A, B, C_simple);
        auto end1 = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> timeSimple = end1 - start1;

        // Timing Blocking GEMM
        auto start2 = chrono::high_resolution_clock::now();
        runBlockingGEMM(M, K, N, A, B, C_blocking, 16); // Block size 16
        auto end2 = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> timeBlocking = end2 - start2;

        // Print Simple Output
        cout << "Algorithm: GEMM Simple\nResult matrix:\n";
        for (int i = 0; i < M; i++) 
        {
            for (int j = 0; j < N; j++) cout << C_simple[i][j] << " ";
            cout << "\n";
        }
        cout << "Execution time: " << timeSimple.count() << " ms\n\n";

        // Print Blocking Output
        cout << "Algorithm: GEMM Blocking\nResult matrix:\n";
        for (int i = 0; i < M; i++) 
        {
            for (int j = 0; j < N; j++) cout << C_blocking[i][j] << " ";
            cout << "\n";
        }
        cout << "Execution time: " << timeBlocking.count() << " ms\n";

    } else if (algo == "csr") {
        CSRGraph graph = convertToCSR(filename, false);
        cout << "Converted graph to CSR with " << graph.numVertices << " vertices and " << graph.numEdges << " edges." << endl;
        
        // Printing CSR conversion arrays including values
        cout << "--- CSR Conversion Output ---\n";
        cout << "row_ptr: ";
        for (size_t i = 0; i < graph.row_ptr.size(); i++) 
        {
            cout << graph.row_ptr[i] << " ";
        }
        cout << "\ncol_idx: ";
        for (size_t i = 0; i < graph.col_idx.size(); i++) 
        {
            cout << graph.col_idx[i] << " ";
        }
        cout << "\nvalues:  ";
        for (size_t i = 0; i < graph.values.size(); i++) 
        {
            cout << graph.values[i] << " ";
        }
        cout << endl;

    } 
    else 
    {
        cout << "Error: Unknown algorithm option." << endl;
    }

    return 0;
}