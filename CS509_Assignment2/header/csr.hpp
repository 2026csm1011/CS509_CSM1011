#ifndef CSR_HPP
#define CSR_HPP
#include <vector>
#include <utility>

struct CSRGraph {
    int V;
    std::vector<int> row_ptr;
    std::vector<int> col_idx;
    std::vector<long long> values;
};

// Converts standard adjacency list to Compressed Sparse Row format
CSRGraph convert_to_csr(int V, const std::vector<std::vector<std::pair<int, long long>>>& adj_list);
#endif