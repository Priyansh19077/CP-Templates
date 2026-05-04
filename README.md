# CP Templates

A collection of competitive programming algorithm templates in C++. Each file is self-contained — copy any function directly into your solution without needing external boilerplate.

## Usage

1. Copy `TemplateStuff/Template.cpp` as your contest starting point.
2. Find the algorithm you need in the relevant category folder.
3. Copy the function or struct into your solution.

## Testing

```bash
make -C tests run
```

All 29 algorithms have tests that run automatically on every push via GitHub Actions.

## Templates

### Boilerplate

| File | Description |
|------|-------------|
| [Template.cpp](TemplateStuff/Template.cpp) | Contest boilerplate: fast I/O, common macros, math utilities, debug helpers |
| [Int_128.cpp](TemplateStuff/Int_128.cpp) | 128-bit integer I/O and debug support |

### Graph Algorithms

| File | Complexity | Description |
|------|-----------|-------------|
| [Dijkstra.cpp](Graph%20Algorithms/Dijkstra.cpp) | O(E log V) | Single-source shortest path (non-negative weights) |
| [BellmanFord.cpp](Graph%20Algorithms/BellmanFord.cpp) | O(VE) | Single-source shortest path; handles negative weights and detects negative cycles |
| [FloydWarshall.cpp](Graph%20Algorithms/FloydWarshall.cpp) | O(V³) | All-pairs shortest paths |
| [Kruskals.cpp](Graph%20Algorithms/Kruskals.cpp) | O(E log E) | Minimum spanning tree |
| [Prims.cpp](Graph%20Algorithms/Prims.cpp) | O(E log V) | Minimum spanning tree (set-based priority queue) |
| [UnionFind.cpp](Graph%20Algorithms/UnionFind.cpp) | O(α(N)) | Disjoint Set Union with path compression and union by rank |
| [Topological_sorting.cpp](Graph%20Algorithms/Topological_sorting.cpp) | O(V+E) | Topological ordering via DFS post-order |
| [KosarajuSCC.cpp](Graph%20Algorithms/KosarajuSCC.cpp) | O(V+E) | Strongly Connected Components via Kosaraju's algorithm |
| [Cycle_in_DAG.cpp](Graph%20Algorithms/Cycle_in_DAG.cpp) | O(V+E) | Cycle detection in a directed graph |
| [EulerianCircuit.cpp](Graph%20Algorithms/EulerianCircuit.cpp) | O(E) | Eulerian path/circuit via Hierholzer's algorithm |
| [FordFulkerson.cpp](Graph%20Algorithms/FordFulkerson.cpp) | O(E · max_flow) | Maximum network flow via DFS augmentation |
| [EdmondsKarp.cpp](Graph%20Algorithms/EdmondsKarp.cpp) | O(VE²) | Maximum network flow via BFS augmentation (Edmonds-Karp) |

### Tree Algorithms

| File | Complexity | Description |
|------|-----------|-------------|
| [LCA_tree.cpp](Tree%20Algorithms/LCA_tree.cpp) | O(N log N) pre / O(log N) query | Lowest Common Ancestor via binary lifting |
| [LCA_O_1.cpp](Tree%20Algorithms/LCA_O_1.cpp) | O(N log N) pre / O(1) query | LCA via Euler tour + sparse table |
| [Binary_Lifting.cpp](Tree%20Algorithms/Binary_Lifting.cpp) | O(N log N) pre / O(log N) query | K-th ancestor queries via binary lifting |
| [HLD.cpp](Tree%20Algorithms/HLD.cpp) | O(log²N) per query | Heavy-Light Decomposition for path queries and updates |
| [Centroid_Tree.cpp](Tree%20Algorithms/Centroid_Tree.cpp) | O(N log N) | Centroid Decomposition |

### Range Queries

| File | Complexity | Description |
|------|-----------|-------------|
| [Segment_tree.cpp](Range%20Queries/Segment_tree.cpp) | O(N) build / O(log N) | Point update, range query — customisable Node and Update |
| [Lazy_SGT.cpp](Range%20Queries/Lazy_SGT.cpp) | O(N) build / O(log N) | Range update, range query with lazy propagation |
| [Sparse_Table.cpp](Range%20Queries/Sparse_Table.cpp) | O(N log N) build / O(1) or O(log N) | Static range queries — O(1) for idempotent ops (min/max) |
| [Mo_algo.cpp](Range%20Queries/Mo_algo.cpp) | O((N+Q)√N) | Offline range queries via Mo's algorithm (distinct count example) |

### String Algorithms

| File | Complexity | Description |
|------|-----------|-------------|
| [String_Hashing.cpp](String%20Algorithms/String_Hashing.cpp) | O(N) pre / O(1) query | Double polynomial hashing for O(1) substring equality checks |
| [Prefix_Function.cpp](String%20Algorithms/Prefix_Function.cpp) | O(N) | KMP prefix (failure) function for pattern matching |
| [ZAlgorithm.cpp](String%20Algorithms/ZAlgorithm.cpp) | O(N) | Z-function for pattern matching |
| [Trie.cpp](String%20Algorithms/Trie.cpp) | O(N) insert/search | Prefix trie for lowercase Latin strings |
| [Suffix_array.cpp](String%20Algorithms/Suffix_array.cpp) | O(N log N) | Suffix array via prefix doubling with counting sort |

### Number Theory

| File | Complexity | Description |
|------|-----------|-------------|
| [MillerRabinDeterministic.cpp](Number%20Theory/MillerRabinDeterministic.cpp) | O(log²N) | Deterministic primality test (correct for all N < 3.3 × 10²⁴) |

### Common Techniques

| File | Complexity | Description |
|------|-----------|-------------|
| [Distinct in Range Queries.cpp](Common%20Techniques/Distinct%20in%20Range%20Queries.cpp) | O((N+Q) log N) | Offline distinct-element count per range via BIT |
| [Fibonacci in LogN.cpp](Common%20Techniques/Fibonacci%20in%20LogN.cpp) | O(log N) | N-th Fibonacci number mod 10⁹+7 via matrix exponentiation |

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md) for how to add new algorithms and tests.

## Author

**Priyansh Agarwal** — [YouTube Channel](https://www.youtube.com/c/PriyanshAgarwal)
