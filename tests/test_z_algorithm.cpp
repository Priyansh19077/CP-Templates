#include "common.h"
#include "../String Algorithms/ZAlgorithm.cpp"

using namespace std;

int run_tests() {
    // "aabxaa" → z = [0, 1, 0, 0, 2, 1]
    auto z = z_function("aabxaa");
    ASSERT_EQ((int)z.size(), 6);
    ASSERT_EQ(z[0], 0); ASSERT_EQ(z[1], 1);
    ASSERT_EQ(z[2], 0); ASSERT_EQ(z[3], 0);
    ASSERT_EQ(z[4], 2); ASSERT_EQ(z[5], 1);

    // "aaaa" → z = [0, 3, 2, 1]
    auto z2 = z_function("aaaa");
    ASSERT_EQ(z2[0], 0); ASSERT_EQ(z2[1], 3);
    ASSERT_EQ(z2[2], 2); ASSERT_EQ(z2[3], 1);

    // Pattern matching: occurrences of "ab" in "ababab" = 3
    string text = "ababab", pattern = "ab";
    string combined = pattern + "$" + text;
    auto z3 = z_function(combined);
    int pLen = (int)pattern.size();
    int count = 0;
    for (int i = pLen + 1; i < (int)combined.size(); i++)
        if (z3[i] >= pLen) count++;
    ASSERT_EQ(count, 3);

    TEST_PASS();
}

int main() { return run_tests(); }
