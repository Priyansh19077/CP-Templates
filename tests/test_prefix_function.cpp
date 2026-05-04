#include "common.h"
#include "../String Algorithms/Prefix_Function.cpp"

using namespace std;

int run_tests() {
    // "aabxaa" → [0, 1, 0, 0, 1, 2]
    auto pi = prefix_function("aabxaa");
    ASSERT_EQ((int)pi.size(), 6);
    ASSERT_EQ(pi[0], 0); ASSERT_EQ(pi[1], 1);
    ASSERT_EQ(pi[2], 0); ASSERT_EQ(pi[3], 0);
    ASSERT_EQ(pi[4], 1); ASSERT_EQ(pi[5], 2);

    // "abcabcd" → [0, 0, 0, 1, 2, 3, 0]
    auto pi2 = prefix_function("abcabcd");
    ASSERT_EQ(pi2[0], 0); ASSERT_EQ(pi2[3], 1);
    ASSERT_EQ(pi2[4], 2); ASSERT_EQ(pi2[5], 3);
    ASSERT_EQ(pi2[6], 0);

    // KMP: count occurrences of "ab" in "ababab" = 3
    string text = "ababab", pattern = "ab";
    string combined = pattern + "#" + text;
    auto pi3 = prefix_function(combined);
    int pLen = (int)pattern.size();
    int count = 0;
    for (int i = pLen + 1; i < (int)combined.size(); i++)
        if (pi3[i] == pLen) count++;
    ASSERT_EQ(count, 3);

    TEST_PASS();
}

int main() { return run_tests(); }
