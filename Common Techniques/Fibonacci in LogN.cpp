// O(log N) — Nth Fibonacci number via matrix exponentiation, modulo 1e9+7
// F(0)=0, F(1)=1, F(2)=1, ...  N can be up to 1e18.
#include <bits/stdc++.h>
using namespace std;

const long long FIB_MOD = 1000000007LL;

vector<vector<long long>> _fib_mul(
        const vector<vector<long long>>& a,
        const vector<vector<long long>>& b) {
    int sz = (int)a.size();
    vector<vector<long long>> c(sz, vector<long long>(sz, 0));
    for (int i = 0; i < sz; i++)
        for (int j = 0; j < sz; j++)
            for (int k = 0; k < sz; k++)
                c[i][k] = (c[i][k] + a[i][j] * b[j][k]) % FIB_MOD;
    return c;
}

vector<vector<long long>> _fib_matpow(vector<vector<long long>> m, long long n) {
    vector<vector<long long>> result = {{1, 0}, {0, 1}};  // identity
    for (; n > 0; n >>= 1) {
        if (n & 1) result = _fib_mul(result, m);
        m = _fib_mul(m, m);
    }
    return result;
}

long long nthFibonacciNumber(long long n) {
    if (n <= 1) return n;
    auto res = _fib_matpow({{1, 1}, {1, 0}}, n - 1);
    return res[0][0];
}
