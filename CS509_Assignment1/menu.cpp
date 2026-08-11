#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

int main() {
    int choice;
    string filename;
    
    do {
        cout << "\n=================================\n";
        cout << "      Assignment 1 Individual Menu \n";
        cout << "=================================\n";
        cout << "1. Run GEMM (Simple & Blocking)\n";
        cout << "2. Run CSR Graph Test\n";
        cout << "0. Exit\n";
        cout << "---------------------------------\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter GEMM filename (e.g., gemm_10.txt): ";
            cin >> filename;
            string cmd = ".\\main.exe gemm " + filename;
            system(cmd.c_str());
        } 
        else if (choice == 2) {
            cout << "Enter CSR filename (e.g., graph_10.txt): ";
            cin >> filename;
            string cmd = ".\\main.exe csr " + filename;
            system(cmd.c_str());
        }

    } while (choice != 0);
    
    return 0;
}