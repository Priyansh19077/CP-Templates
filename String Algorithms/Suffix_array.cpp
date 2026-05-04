// O(N log N) — Suffix Array construction via prefix doubling + counting sort
// suffixArray(s) appends '$' and returns the suffix array p[] where p[i] is the starting
// index of the i-th lexicographically smallest suffix.
#include <algorithm>
#include <string>
#include <vector>

static void _counting_sort(std::vector<int>& p, std::vector<int>& c) {
    int n = (int)p.size();
    std::vector<int> cnt(n, 0);
    for (int x : c) cnt[x]++;
    std::vector<int> pos(n, 0);
    for (int i = 1; i < n; i++) pos[i] = pos[i - 1] + cnt[i - 1];
    std::vector<int> p_new(n);
    for (int x : p) p_new[pos[c[x]]++] = x;
    p = p_new;
}

std::vector<int> suffixArray(const std::string& s_in) {
    std::string s = s_in + '$';
    int n = (int)s.size();
    std::vector<int> p(n), c(n);

    // Initial sort by single character
    std::vector<std::pair<char, int>> a(n);
    for (int i = 0; i < n; i++) a[i] = {s[i], i};
    std::sort(a.begin(), a.end());
    for (int i = 0; i < n; i++) p[i] = a[i].second;
    c[p[0]] = 0;
    for (int i = 1; i < n; i++)
        c[p[i]] = c[p[i - 1]] + (a[i].first != a[i - 1].first ? 1 : 0);

    for (int k = 0; (1 << k) < n; k++) {
        for (int i = 0; i < n; i++) p[i] = (p[i] - (1 << k) + n) % n;
        _counting_sort(p, c);
        std::vector<int> c_new(n);
        c_new[p[0]] = 0;
        for (int i = 1; i < n; i++) {
            std::pair<int, int> prev = {c[p[i - 1]], c[(p[i - 1] + (1 << k)) % n]};
            std::pair<int, int> cur  = {c[p[i]],     c[(p[i]     + (1 << k)) % n]};
            c_new[p[i]] = c_new[p[i - 1]] + (cur != prev ? 1 : 0);
        }
        c = c_new;
    }
    return p;
}
