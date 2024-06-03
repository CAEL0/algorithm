// BOJ 13505 두 수 XOR

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

struct Node {
    int zero = -1;
    int one = -1;
};

struct Trie {
    vector<Node> nodes;

    Trie() { nodes.push_back(Node()); }

    void insert(int cur, int x, int bit) {
        if (bit == 0)
            return;

        if (x & bit) {
            if (nodes[cur].one == -1) {
                nodes[cur].one = nodes.sz;
                nodes.push_back(Node());
            }

            insert(nodes[cur].one, x, bit >> 1);
        } else {
            if (nodes[cur].zero == -1) {
                nodes[cur].zero = nodes.sz;
                nodes.push_back(Node());
            }

            insert(nodes[cur].zero, x, bit >> 1);
        }
    }

    int minimum(int cur, int x, int bit) {
        if (bit == 0)
            return 0;

        if (x & bit) {
            if (nodes[cur].one == -1)
                return bit + minimum(nodes[cur].zero, x, bit >> 1);

            return minimum(nodes[cur].one, x, bit >> 1);
        }

        if (nodes[cur].zero == -1)
            return bit + minimum(nodes[cur].one, x, bit >> 1);

        return minimum(nodes[cur].zero, x, bit >> 1);
    }

    int maximum(int cur, int x, int bit) {
        if (bit == 0)
            return 0;

        if (x & bit) {
            if (nodes[cur].zero == -1)
                return maximum(nodes[cur].one, x, bit >> 1);

            return bit + maximum(nodes[cur].zero, x, bit >> 1);
        }

        if (nodes[cur].one == -1)
            return maximum(nodes[cur].zero, x, bit >> 1);

        return bit + maximum(nodes[cur].one, x, bit >> 1);
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<int> v(n);
    for (int i = 0; i < n; i++)
        cin >> v[i];

    Trie trie;
    int bit = (1 << 29);

    for (int x : v)
        trie.insert(0, x, bit);

    int ans = 0;
    for (int x : v)
      ans = max(ans, trie.maximum(0, x, bit));

    cout << ans;
}
