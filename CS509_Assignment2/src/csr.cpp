#include "../header/csr.hpp"
#include <cstddef>

CSRGraph convert_to_csr(int V, const std::vector<std::vector<std::pair<int, long long>>>& adj_list) {
    CSRGraph csr;
    csr.V = V;
    csr.row_ptr.push_back(0);
    for (int i = 0; i < V; ++i) {
        for (size_t j = 0; j < adj_list[i].size(); ++j) 
        {
            csr.col_idx.push_back(adj_list[i][j].first);
            csr.values.push_back(adj_list[i][j].second);
        }
        csr.row_ptr.push_back(csr.col_idx.size());
    }
    return csr;
}