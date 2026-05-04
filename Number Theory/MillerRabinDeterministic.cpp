// O(log²N) — Deterministic Miller-Rabin primality test (correct for all N < 3.3 × 10²⁴)
// MillerRabin(n) returns true if n is prime, false otherwise.
// Uses __int128 for intermediate multiplication to avoid overflow.
#include <bits/stdc++.h>
using namespace std;

__int128 _mr_pow(__int128 a, __int128 b, __int128 mod) {
    __int128 res = 1;
    for (a %= mod; b > 0; b >>= 1) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
    }
    return res;
}

bool _mr_composite(__int128 n, __int128 a, long long d, int s) {
    __int128 x = _mr_pow(a, d, n);
    if (x == 1 || x == n - 1) return false;
    for (int r = 1; r < s; r++) {
        x = x * x % n;
        if (x == n - 1) return false;
    }
    return true;
}

bool MillerRabin(__int128 n) {
    if (n < 2) return false;
    long long d = (long long)(n - 1);
    int s = 0;
    while ((d & 1) == 0) { d >>= 1; s++; }
    for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n == (__int128)a) return true;
        if (_mr_composite(n, a, d, s)) return false;
    }
    return true;
}
