#include <iostream>
#include <string>
#include "../header/csr.hpp"
#include "../header/algorithm.hpp"

using namespace std;

void Menu() 
{
    cout << "       CS509 - MST Algorithms        \n";
    cout << "1. Run Kruskal's Algorithm\n";
    cout << "2. Run Prim's Algorithm\n";
    cout << "3. Run Both (Comparison Mode)\n";
    cout << "4. Exit\n";
    cout << "Select an option: ";
}

int main() 
{
    int choice;
    string filename;
    CSRGraph graph;

    while (true) 
{
        Menu();
        if (!(cin >> choice)) 
        {
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        if (choice == 4) break;

        if (choice >= 1 && choice <= 3) 
        {
            cout << "Enter the input file path: ";
            cin >> filename;

            cout << "\nLoading file and converting to CSR...\n";
            if (!ConvertToCSR(filename, graph)) 
            {
                continue; 
            }
            cout << "Graph loaded successfully! (V = " << graph.V << ", E = " << graph.E << ")\n\n";

            if (choice == 1 || choice == 3) 
            {
                Kruskal(graph);
            }
            if (choice == 2 || choice == 3) 
            {
                Prim(graph);
            }
        } 
        else 
        {
            cout << "Invalid choice. Please select 1-4.\n";
        }
    }

    return 0;
}