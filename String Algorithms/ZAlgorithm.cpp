// O(N) — Z-function
// z[i] = length of the longest substring starting at s[i] that matches a prefix of s
// z[0] = 0 by convention. Use for pattern matching: build z on pattern + "$" + text,
// look for z[i] >= len(pattern).
#include <bits/stdc++.h>
using namespace std;

vector<int> z_function(const string& s) {
    int n = (int)s.size();
    vector<int> z(n, 0);
    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i <= r) z[i] = min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] - 1 > r) { l = i; r = i + z[i] - 1; }
    }
    return z;
}
