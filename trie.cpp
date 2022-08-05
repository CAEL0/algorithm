#include <iostream>
#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

struct Node {
    int idx[26];
    bool finish;
};
struct Trie {
    vector<Node> nodes{Node()};

    void insert(const string s) {
        int cur = 0;
        for (char c: s) {
            if (!nodes[cur].idx[c - 97]) {
                nodes[cur].idx[c - 97] = nodes.size();
                nodes.push_back(Node());
            }
            cur = nodes[cur].idx[c - 97];
        }
        nodes[cur].finish = true;
    }
    bool search(const string s) {
        int cur = 0;
        for (char c: s) {
            if (!nodes[cur].idx[c - 97]) {
                return false;
            }
            cur = nodes[cur].idx[c - 97];
        }
        return nodes[cur].finish;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    
}
