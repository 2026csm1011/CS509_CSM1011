# CS509-PGSL: Assignment 4
**Task Type:** Individual (Vertex Coloring & PageRank)
---

## 1. Vertex Coloring Results 

| File | V | E | Colors Used | Valid? | Time | Status |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| `color_10.txt` | 10 | 20 | 4 | Yes | 0 ms | Pass |
| `color_100.txt` | 100 | 300 | 5 | Yes | 0 ms | Pass |
| `color_10000.txt` | 10,000 | 30,000 | 6 | Yes | 16.2274 ms | Pass |
| `color_50000.txt` | 50,000 | 150,000 | 6 | Yes | 78.1047 ms | Pass |
| `color_100000.txt`| 100,000 | 200000 | 5 | Yes | 136.004 ms | Pass |

---

## 2. PageRank Results (Table 10.2)

| File | V | E | Damping | Top Vertex | Sum of Ranks | Iter. / Time | Status |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| `pagerank_10.txt` | 10 | 25 | 0.85 | 3 | ~1.000000 | 13 / 0 ms | Pass |
| `pagerank_100.txt`| 100 | 250 | 0.85 | 94 | ~1.000000 | 15 / 0 ms | Pass |
| `pagerank_1000.txt`| 1,000 | 3,000 | 0.85 | 200 | ~1.000000 | 14 /  0.998000 ms | Pass |
| `pagerank_10000.txt`| 10,000 | 30,000 | 0.85 | 9597 | ~1.000000 | 14 /  15.955300 ms | Pass |
| `pagerank_50000.txt`| 50,000 | 150,000 | 0.85 | 15755 | ~1.000000 | 15 /  91.754400 ms | Pass |
