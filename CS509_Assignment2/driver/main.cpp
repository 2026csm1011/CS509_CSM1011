#include "../header/menu.hpp"
#include "../header/algorithms.hpp"
#include "../header/generator.hpp"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>

using namespace std;

string intToString(int n) {
    stringstream ss;
    ss << n;
    return ss.str();
}

int main(int argc, char* argv[]) {
    // 1. Direct Command-Line Execution
    if (argc == 3) {
        string algo = argv[1];
        string filename = argv[2];
        if (algo == "BF") run_bellman_ford_task(filename);
        else if (algo == "FW") run_floyd_warshall_task(filename);
        else cout << "Unknown algorithm! Use BF or FW.\n";
        return 0;
    }

    // 2. Interactive Menu Mode
    srand(time(0)); // Initialize random seed for generator
    int choice;
    string filename;
    
    cout << "\n--- Assignment 2: Individual Tasks ---\n";
    cout << "1. Run Bellman-Ford\n";
    cout << "2. Run Floyd-Warshall\n";
    cout << "3. Generate all standard test files\n";
    cout << "Select option: ";
    cin >> choice;

    if (choice == 1) {
        cout << "Enter input file path: ";
        cin >> filename;
        run_bellman_ford_task(filename);
    } 
    else if (choice == 2) {
        cout << "Enter input file path: ";
        cin >> filename;
        run_floyd_warshall_task(filename);
    } 
    else if (choice == 3) {
        // Generates exact sizes required by the rubric[cite: 1]
        int bfSizes[] = {10, 100, 10000, 50000, 100000};
        for (int i = 0; i < 5; i++) {
            generateBellmanFordGraph(bfSizes[i], "bf_" + intToString(bfSizes[i]) + ".txt");
            cout << "Generated bf_" << bfSizes[i] << ".txt\n";
        }
        
        int fwSizes[] = {10, 100, 500, 1000, 2000};
        for (int i = 0; i < 5; i++) {
            generateFloydWarshallMatrix(fwSizes[i], "fw_" + intToString(fwSizes[i]) + ".txt");
            cout << "Generated fw_" << fwSizes[i] << ".txt\n";
        }

        generateNegativeCycleTest("bf_negative_cycle.txt");
        cout << "Generated bf_negative_cycle.txt\n";
    }
    
    return 0;
}