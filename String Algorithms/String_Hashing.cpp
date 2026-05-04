// O(N) preprocessing, O(1) per substring hash query — double polynomial hashing
// substringHash(l, r) returns a pair of hashes for s[l..r]; compare pairs to check equality.
// Two equal substrings always return the same pair (collision probability negligible).
#include <bits/stdc++.h>
using namespace std;

struct Hashing {
    static constexpr long long BASE = 31;
    static constexpr long long MOD1 = 1000000009LL;
    static constexpr long long MOD2 = 100000007LL;

    int n;
    vector<long long> h1, h2, pw1, pw2, inv1, inv2;

    long long _pow(long long a, long long b, long long mod) {
        long long res = 1;
        for (a %= mod; b > 0; b >>= 1) {
            if (b & 1) res = res * a % mod;
            a = a * a % mod;
        }
        return res;
    }
    long long _mul(long long a, long long b, long long mod) { return a % mod * (b % mod) % mod; }
    long long _sub(long long a, long long b, long long mod) { return ((a - b) % mod + mod) % mod; }

    Hashing(const string& s) : n((int)s.size()), h1(n), h2(n),
            pw1(n + 1), pw2(n + 1), inv1(n + 1), inv2(n + 1) {
        pw1[0] = pw2[0] = 1;
        for (int i = 1; i <= n; i++) { pw1[i] = pw1[i-1] * BASE % MOD1; pw2[i] = pw2[i-1] * BASE % MOD2; }
        inv1[n] = _pow(pw1[n], MOD1 - 2, MOD1);
        inv2[n] = _pow(pw2[n], MOD2 - 2, MOD2);
        for (int i = n - 1; i >= 0; i--) { inv1[i] = inv1[i+1] * BASE % MOD1; inv2[i] = inv2[i+1] * BASE % MOD2; }
        for (int i = 0; i < n; i++) {
            long long c = s[i] - 'a' + 1;
            h1[i] = (c * pw1[i] % MOD1 + (i > 0 ? h1[i-1] : 0)) % MOD1;
            h2[i] = (c * pw2[i] % MOD2 + (i > 0 ? h2[i-1] : 0)) % MOD2;
        }
    }

    // Returns {hash1, hash2} for s[l..r] (0-indexed, inclusive)
    pair<long long, long long> substringHash(int l, int r) {
        long long v1 = _mul(_sub(h1[r], l > 0 ? h1[l-1] : 0, MOD1), inv1[l], MOD1);
        long long v2 = _mul(_sub(h2[r], l > 0 ? h2[l-1] : 0, MOD2), inv2[l], MOD2);
        return {v1, v2};
    }
};
