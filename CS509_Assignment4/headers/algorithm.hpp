#ifndef ALGO_H
#define ALGO_H

#include <string>
#include "csr.hpp"

// Task Wrappers called by main.cpp
void runVertexColoringTask(const std::string& filepath);
void runPageRankTask(const std::string& filepath);

// Core Algorithms
void vertexColoring(const CSRGraph& graph);
void pageRank(const CSRGraph& graph, double damping, double tolerance, int max_iterations);

#endif