#include "common.h"
#include "../String Algorithms/String_Hashing.cpp"

using namespace std;

int run_tests() {
    Hashing h("abcabcabc");

    // Same substrings must have equal hashes
    auto h1 = h.substringHash(0, 2);  // "abc"
    auto h2 = h.substringHash(3, 5);  // "abc"
    auto h3 = h.substringHash(6, 8);  // "abc"
    ASSERT_TRUE(h1 == h2);
    ASSERT_TRUE(h1 == h3);

    // Different substrings must differ
    auto h4 = h.substringHash(0, 1);  // "ab"
    auto h5 = h.substringHash(1, 2);  // "bc"
    ASSERT_TRUE(h4 != h5);
    ASSERT_TRUE(h1 != h4);

    // Single characters
    Hashing h2_obj("aab");
    auto ha1 = h2_obj.substringHash(0, 0);  // "a"
    auto ha2 = h2_obj.substringHash(1, 1);  // "a"
    auto hb  = h2_obj.substringHash(2, 2);  // "b"
    ASSERT_TRUE(ha1 == ha2);
    ASSERT_TRUE(ha1 != hb);

    TEST_PASS();
}

int main() { return run_tests(); }
