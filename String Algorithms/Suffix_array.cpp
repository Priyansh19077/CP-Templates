// O(N log N) — Suffix Array construction via prefix doubling + counting sort
// suffixArray(s) appends '$' and returns the suffix array p[] where p[i] is the starting
// index of the i-th lexicographically smallest suffix.
#include <bits/stdc++.h>
using namespace std;

void _counting_sort(vector<int>& p, vector<int>& c) {
    int n = (int)p.size();
    vector<int> cnt(n, 0);
    for (int x : c) cnt[x]++;
    vector<int> pos(n, 0);
    for (int i = 1; i < n; i++) pos[i] = pos[i - 1] + cnt[i - 1];
    vector<int> p_new(n);
    for (int x : p) p_new[pos[c[x]]++] = x;
    p = p_new;
}

vector<int> suffixArray(const string& s_in) {
    string s = s_in + '$';
    int n = (int)s.size();
    vector<int> p(n), c(n);

    // Initial sort by single character
    vector<pair<char, int>> a(n);
    for (int i = 0; i < n; i++) a[i] = {s[i], i};
    sort(a.begin(), a.end());
    for (int i = 0; i < n; i++) p[i] = a[i].second;
    c[p[0]] = 0;
    for (int i = 1; i < n; i++)
        c[p[i]] = c[p[i - 1]] + (a[i].first != a[i - 1].first ? 1 : 0);

    for (int k = 0; (1 << k) < n; k++) {
        for (int i = 0; i < n; i++) p[i] = (p[i] - (1 << k) + n) % n;
        _counting_sort(p, c);
        vector<int> c_new(n);
        c_new[p[0]] = 0;
        for (int i = 1; i < n; i++) {
            pair<int, int> prev = {c[p[i - 1]], c[(p[i - 1] + (1 << k)) % n]};
            pair<int, int> cur  = {c[p[i]],     c[(p[i]     + (1 << k)) % n]};
            c_new[p[i]] = c_new[p[i - 1]] + (cur != prev ? 1 : 0);
        }
        c = c_new;
    }
    return p;
}
