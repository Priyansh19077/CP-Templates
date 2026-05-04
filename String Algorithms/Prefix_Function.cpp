// O(N) — KMP prefix function (failure function)
// pi[i] = length of longest proper prefix of s[0..i] that is also a suffix
// Use for pattern matching: build pi on pattern + "#" + text, look for pi[i] == len(pattern)
#include <bits/stdc++.h>
using namespace std;

vector<int> prefix_function(const string& s) {
    int n = (int)s.size();
    vector<int> pi(n, 0);
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) j++;
        pi[i] = j;
    }
    return pi;
}
