#include <iostream>
#include <cstdlib>

using namespace std;

void run_assignment1() 
{
    cout << "\n>>> Starting Assignment 1...\n\n";
 
#ifdef _WIN32
    
    system("cd ../CS509_Assignment1 && .\\menu.exe");
#else
    
    system("cd ../CS509_Assignment1 && ./menu");
#endif
    
    cout << "\n<<< Returning to Common Wrapper...\n\n";
}
void run_assignment2()
{
    cout << "\n>>> Starting Assignment 2...\n\n";
#ifdef _WIN32    
    system("cd ../CS509_Assignment2 && .\\graph_driver.exe");
#else
    system("cd ../CS509_Assignment2 && ./graph_driver");
#endif
    
    cout << "\n<<< Returning to Common Wrapper...\n\n";
}

int main() {
    int choice;
    
    do {
        cout << "=================================\n";
        cout << "      Common Wrapper             \n";
        cout << "=================================\n";
        cout << "1. Run Assignment 1\n";
        cout << "2. Run Assignment 2\n";
        cout << "0. Exit\n";
        cout << "---------------------------------\n";
        cout << "Select Assignment: ";
        cin >> choice;

        switch(choice) {
            case 1:
                run_assignment1();
                break;
            case 2:
                run_assignment2();
                break;   
            case 0:
                cout << "Exiting Common Wrapper...\n";
                break;
                
            default:
                cout << "Invalid choice. .\n\n";
        }
        
    } while(choice != 0);
    
    return 0;
}