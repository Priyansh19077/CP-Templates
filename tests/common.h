#pragma once
#include <algorithm>
#include <cassert>
#include <climits>
#include <cmath>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

// Simple assertion macros — print file/line on failure and return 1
#define ASSERT_EQ(a, b) do { \
    auto _a = (a); auto _b = (b); \
    if (_a != _b) { \
        std::cerr << "FAIL " << __FILE__ << ":" << __LINE__ \
                  << "\n  expected: " << _b << "\n  got:      " << _a << "\n"; \
        return 1; \
    } \
} while (0)

#define ASSERT_TRUE(cond) do { \
    if (!(cond)) { \
        std::cerr << "FAIL " << __FILE__ << ":" << __LINE__ \
                  << ": " << #cond << "\n"; \
        return 1; \
    } \
} while (0)

#define ASSERT_FALSE(cond) ASSERT_TRUE(!(cond))

#define TEST_PASS() do { \
    std::cout << __FILE__ << ": all tests passed\n"; \
    return 0; \
} while (0)
