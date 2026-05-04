#include "common.h"
#include "../Common Techniques/Fibonacci in LogN.cpp"

using namespace std;

int run_tests() {
    // F(0)=0, F(1)=1, F(2)=1, F(10)=55
    ASSERT_EQ(nthFibonacciNumber(0), 0LL);
    ASSERT_EQ(nthFibonacciNumber(1), 1LL);
    ASSERT_EQ(nthFibonacciNumber(2), 1LL);
    ASSERT_EQ(nthFibonacciNumber(10), 55LL);

    // F(50) mod 1e9+7 = 586268941
    ASSERT_EQ(nthFibonacciNumber(50), 586268941LL);

    // F(20) = 6765
    ASSERT_EQ(nthFibonacciNumber(20), 6765LL);

    TEST_PASS();
}

int main() { return run_tests(); }
