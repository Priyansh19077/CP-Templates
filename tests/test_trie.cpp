#include "common.h"
#include "../String Algorithms/Trie.cpp"

using namespace std;

int run_tests() {
    Trie trie;

    trie.add_string("apple");
    trie.add_string("app");
    trie.add_string("application");

    // "app" was explicitly inserted → leaf count = 1
    int node = 0;
    for (char c : string("app")) {
        int idx = c - 'a';
        ASSERT_TRUE(trie.trie_tree[node].next[idx] != -1);
        node = trie.trie_tree[node].next[idx];
    }
    ASSERT_EQ(trie.trie_tree[node].is_a_leaf, 1);

    // "apple" ends at its own node → leaf count = 1
    int node2 = 0;
    for (char c : string("apple")) {
        int idx = c - 'a';
        ASSERT_TRUE(trie.trie_tree[node2].next[idx] != -1);
        node2 = trie.trie_tree[node2].next[idx];
    }
    ASSERT_EQ(trie.trie_tree[node2].is_a_leaf, 1);

    // "ap" is not a complete word → not a leaf
    int node3 = 0;
    for (char c : string("ap")) node3 = trie.trie_tree[node3].next[c - 'a'];
    ASSERT_EQ(trie.trie_tree[node3].is_a_leaf, 0);

    // "xyz" path doesn't exist
    ASSERT_EQ(trie.trie_tree[0].next['x' - 'a'], -1);

    TEST_PASS();
}

int main() { return run_tests(); }
