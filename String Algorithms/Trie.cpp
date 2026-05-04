// O(N) insert and prefix search — Trie for lowercase Latin strings
// Call trie.add_string(s) to insert. To search, traverse trie_tree[node].next.
// trie_tree[node].is_a_leaf counts how many inserted strings end at this node.
#include <bits/stdc++.h>
using namespace std;

struct TrieNode {
    vector<int> next;
    int is_a_leaf = 0;
    TrieNode() : next(26, -1) {}
};

struct Trie {
    vector<TrieNode> trie_tree;
    Trie() { trie_tree.emplace_back(); }

    void add_string(const string& s) {
        int cur = 0;
        for (char c : s) {
            int idx = c - 'a';
            if (trie_tree[cur].next[idx] == -1) {
                trie_tree[cur].next[idx] = (int)trie_tree.size();
                trie_tree.emplace_back();
            }
            cur = trie_tree[cur].next[idx];
        }
        trie_tree[cur].is_a_leaf++;
    }
};
