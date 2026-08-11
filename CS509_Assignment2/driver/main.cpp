#include <iostream>
#include <string>
#include "../header/menu.hpp"
#include"../header/algorithms.hpp"

using namespace std;

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
    run_assignment_2_menu();
    
    return 0;
}