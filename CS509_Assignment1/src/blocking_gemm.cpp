#include "../headers/helper.hpp"
#include <algorithm>

using namespace std;

void runBlockingGEMM(int M, int K, int N, const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C, int blockSize) {
    for (int ii = 0; ii < M; ii += blockSize) {
        for (int jj = 0; jj < N; jj += blockSize) {
            for (int kk = 0; kk < K; kk += blockSize) {
                for (int i = ii; i < min(ii + blockSize, M); ++i) {
                    for (int j = jj; j < min(jj + blockSize, N); ++j) {
                        int sum = 0;
                        for (int k = kk; k < min(kk + blockSize, K); ++k) {
                            sum += A[i][k] * B[k][j];
                        }
                        C[i][j] += sum;
                    }
                }
            }
        }
    }
}