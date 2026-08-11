#ifndef GENERATOR_HPP
#define GENERATOR_HPP
#include <string>

void generateBellmanFordGraph(int V, std::string filename);
void generateFloydWarshallMatrix(int V, std::string filename);
void generateNegativeCycleTest(std::string filename);
#endif