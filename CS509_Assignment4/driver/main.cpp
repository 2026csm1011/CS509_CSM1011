#include<iostream>
#include <string>
#include "../headers/algorithm.hpp"

int main(int argc, char* argv[]) {
    int choice;
    std::string filepath;

    std::cout << "Select Algorithm:\n";
    std::cout << "1. Vertex Coloring\n";
    std::cout << "2. PageRank\n";
    std::cout << "Enter choice: ";
    std::cin >> choice;

    std::cout << "Enter input file path (e.g., test/color_10.txt): ";
    std::cin >> filepath;
    switch (choice) {
        case 1:
            runVertexColoringTask(filepath);
            break;
        case 2:
            runPageRankTask(filepath);
            break;
        default:
            std::cerr << "Invalid choice. Please select 1 or 2.\n";
            break;
    }

    return 0;
}