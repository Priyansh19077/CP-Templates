#include "common.h"
#include "../Range Queries/Mo_algo.cpp"

using namespace std;

int run_tests() {
    // arr = [1, 2, 3, 2, 1, 4, 3]
    // Queries (0-indexed, inclusive):
    //   (0, 2) → {1,2,3} → 3 distinct
    //   (1, 4) → {2,3,2,1} → {1,2,3} → 3 distinct
    //   (0, 6) → all → {1,2,3,4} → 4 distinct
    //   (3, 5) → {2,1,4} → 3 distinct
    vector<int> arr = {1, 2, 3, 2, 1, 4, 3};
    vector<pair<int, int>> queries = {{0, 2}, {1, 4}, {0, 6}, {3, 5}};

    vector<int> ans = moDistinctQueries(7, arr, queries);
    ASSERT_EQ(ans[0], 3);
    ASSERT_EQ(ans[1], 3);
    ASSERT_EQ(ans[2], 4);
    ASSERT_EQ(ans[3], 3);

    TEST_PASS();
}

int main() { return run_tests(); }
