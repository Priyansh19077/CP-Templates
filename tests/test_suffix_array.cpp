#include "common.h"
#include "../String Algorithms/Suffix_array.cpp"

using namespace std;

int run_tests() {
    // Suffix array of "banana$":
    // Suffixes sorted: $, a$, ana$, anana$, banana$, na$, nana$
    // Indices:          6,  5,  3,    1,      0,      4,   2
    vector<int> sa = suffixArray("banana");
    ASSERT_EQ((int)sa.size(), 7);  // "banana$" has 7 chars
    ASSERT_EQ(sa[0], 6);  // "$"
    ASSERT_EQ(sa[1], 5);  // "a$"
    ASSERT_EQ(sa[2], 3);  // "ana$"
    ASSERT_EQ(sa[3], 1);  // "anana$"
    ASSERT_EQ(sa[4], 0);  // "banana$"
    ASSERT_EQ(sa[5], 4);  // "na$"
    ASSERT_EQ(sa[6], 2);  // "nana$"

    // "aab$": sorted suffixes: $, aab$, ab$, b$  → [3, 0, 1, 2]
    vector<int> sa2 = suffixArray("aab");
    ASSERT_EQ(sa2[0], 3);  // "$"
    ASSERT_EQ(sa2[1], 0);  // "aab$"
    ASSERT_EQ(sa2[2], 1);  // "ab$"
    ASSERT_EQ(sa2[3], 2);  // "b$"

    TEST_PASS();
}

int main() { return run_tests(); }
