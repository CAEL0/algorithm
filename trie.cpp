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

        for (char c : s) {
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

        for (char c : s) {
            if (!nodes[cur].idx[c - 97])
                return false;

            cur = nodes[cur].idx[c - 97];
        }

        return nodes[cur].finish;
    }
};

//--------------------------------------------------------------------------------

struct Trie {
    map<char, Trie *> nxt;
    bool finish;

    Trie() { finish = false; }

    ~Trie() { nxt.clear(); }

    bool insert(const char *s) {
        if (*s == '\0') {
            finish = true;
            return !nxt.sz;
        }

        if (finish)
            return false;

        if (nxt.find(*s) == nxt.end())
            nxt[*s] = new Trie;

        return nxt[*s]->insert(s + 1);
    }
};

//--------------------------------------------------------------------------------

struct Trie {
    vector<pair<char, Trie *>> nxt;
    bool finish;

    Trie() { finish = false; }

    ~Trie() { nxt.clear(); }

    void insert(const char *s) {
        if (*s == '\0') {
            finish = true;
            return;
        }

        for (auto node : nxt) {
            if (node.fi == *s) {
                node.se->insert(s + 1);
                return;
            }
        }

        nxt.push_back({*s, new Trie});
        nxt.bk.se->insert(s + 1);
    }
};
