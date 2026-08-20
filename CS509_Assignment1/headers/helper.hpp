#ifndef HELPER_HPP
#define HELPER_HPP

#include <vector>
#include <string>

using namespace std;

struct CSRGraph 
{
    int numVertices;
    int numEdges;
    vector<int> row_ptr;
    vector<int> col_idx;
    vector<int> values;
};

void runSimpleGEMM(int M, int K, int N, const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C);
void runBlockingGEMM(int M, int K, int N, const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C, int blockSize);
CSRGraph convertToCSR(const string& filename, bool isWeighted);

#endif