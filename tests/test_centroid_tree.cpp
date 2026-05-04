#include "common.h"
#include "../Tree Algorithms/Centroid_Tree.cpp"

using namespace std;

int run_tests() {
    // Path graph: 0-1-2-3-4 (5 nodes)
    // Centroid of the full tree is node 2
    int n = 5;
    edgeList.clear();
    deleted.clear();
    subtree.resize(n);
    fill(subtree.begin(), subtree.end(), 0);

    vector<int> edges[5];
    for (int i = 0; i < n - 1; i++) {
        edges[i].push_back((int)edgeList.size());
        edges[i + 1].push_back((int)edgeList.size());
        edgeList.push_back({i, i + 1});
        deleted.push_back(false);
    }

    int root = decompose(0, edges, new vector<int>[n], -1);
    ASSERT_EQ(root, 2);  // centroid of 0-1-2-3-4 is node 2

    // Star graph: center=0, leaves 1,2,3,4 — centroid is node 0
    int n2 = 5;
    edgeList.clear();
    deleted.clear();
    subtree.assign(n2, 0);

    vector<int> edges2[5];
    for (int i = 1; i < n2; i++) {
        edges2[0].push_back((int)edgeList.size());
        edges2[i].push_back((int)edgeList.size());
        edgeList.push_back({0, i});
        deleted.push_back(false);
    }

    int root2 = decompose(0, edges2, new vector<int>[n2], -1);
    ASSERT_EQ(root2, 0);

    TEST_PASS();
}

int main() { return run_tests(); }
