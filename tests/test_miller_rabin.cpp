#include "common.h"
#include "../Number Theory/MillerRabinDeterministic.cpp"

using namespace std;

int run_tests() {
    // Known primes
    ASSERT_TRUE(MillerRabin(2));
    ASSERT_TRUE(MillerRabin(3));
    ASSERT_TRUE(MillerRabin(5));
    ASSERT_TRUE(MillerRabin(7));
    ASSERT_TRUE(MillerRabin(97));
    ASSERT_TRUE(MillerRabin(1000000007));
    ASSERT_TRUE(MillerRabin(998244353));

    // Known composites
    ASSERT_FALSE(MillerRabin(1));
    ASSERT_FALSE(MillerRabin(4));
    ASSERT_FALSE(MillerRabin(6));
    ASSERT_FALSE(MillerRabin(9));
    ASSERT_FALSE(MillerRabin(100));
    ASSERT_FALSE(MillerRabin(1000000006));

    // Large prime
    ASSERT_TRUE(MillerRabin((__int128)1e18 + 9));

    TEST_PASS();
}

int main() { return run_tests(); }
