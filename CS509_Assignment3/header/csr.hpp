#ifndef CSR_HPP
#define CSR_HPP

#include <vector>
#include <string>

// Compressed Sparse Row (CSR) Graph representation
struct CSRGraph {
    std::vector<int> row_ptr;
    std::vector<int> col_idx;
    std::vector<int> values;
    int V;
    int E;
};

// Helper function to read the text file and convert to CSR
bool ConvertToCSR(const std::string& filename, CSRGraph& graph);

#endif 