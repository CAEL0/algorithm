// BOJ 9250 문자열 집합 판별

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

struct Trie {
    vector<Trie *> go;
    Trie *fail;
    bool output;

    Trie() {
        go.resize(26);
        output = false;
    }

    void insert(string &s, int idx) {
        if (idx == s.sz) {
            output = true;
            return;
        }

        int nxt = (s[idx] - 'a');
        if (!go[nxt])
            go[nxt] = new Trie;

        go[nxt]->insert(s, idx + 1);
    }
};

struct AhoCorasick {
    Trie *root;

    AhoCorasick(vector<string> &v) {
        root = new Trie;
        root->fail = root;

        for (string &s : v)
            root->insert(s, 0);

        deque<Trie *> dq = {root};

        while (dq.sz) {
            Trie *cur = dq.front();
            dq.pop_front();

            for (int i = 0; i < 26; i++) {
                Trie *nxt = cur->go[i];
                if (nxt == nullptr)
                    continue;

                if (cur == root)
                    nxt->fail = root;
                else {
                    Trie *dst = cur->fail;
                    while (dst != root && !(dst->go[i]))
                        dst = dst->fail;

                    if (dst->go[i])
                        dst = dst->go[i];

                    nxt->fail = dst;
                }

                if (nxt->fail->output)
                    nxt->output = true;

                dq.push_back(nxt);
            }
        }
    }

    bool find(string &s) {
        Trie *cur = root;

        for (char c : s) {
            int nxt = c - 'a';
            while (cur != root && !cur->go[nxt])
                cur = cur->fail;

            if (cur->go[nxt])
                cur = cur->go[nxt];

            if (cur->output)
                return true;
        }

        return false;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<string> v(n);
    for (int i = 0; i < n; i++)
        cin >> v[i];

    AhoCorasick ac(v);

    int q;
    cin >> q;

    while (q--) {
        string s;
        cin >> s;

        cout << (ac.find(s) ? "YES" : "NO") << '\n';
    }
}

//--------------------------------------------------------------------------------

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

struct Trie {
    vector<pair<char, Trie *>> go;
    Trie *fail;
    bool output;

    Trie() { output = false; }
    ~Trie() { go.clear(); }
    void insert(const char *s) {
        if (*s == '\0') {
            output = true;
            return;
        }
        for (auto node : go) {
            if (node.fi == *s) {
                node.se->insert(s + 1);
                return;
            }
        }
        go.push_back({*s, new Trie});
        go.bk.se->insert(s + 1);
    }
};
Trie *root;

void init(int n) {
    root = new Trie;
    while (n--) {
        char s[105];
        cin >> s;
        root->insert(s);
    }
    queue<Trie *> que;
    root->fail = root;
    que.push(root);
    while (que.sz) {
        Trie *cur = que.front();
        que.pop();
        for (auto &node : cur->go) {
            if (cur == root)
                node.se->fail = root;
            else {
                Trie *dst = cur->fail;
                while (dst != root) {
                    bool flag = false;
                    for (auto z : dst->go) {
                        if (node.fi == z.fi) {
                            flag = true;
                            break;
                        }
                    }
                    if (flag)
                        break;

                    dst = dst->fail;
                }
                for (auto z : dst->go) {
                    if (node.fi == z.fi) {
                        dst = z.se;
                        break;
                    }
                }
                node.se->fail = dst;
            }
            if (node.se->fail->output)
                node.se->output = true;

            que.push(node.se);
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, q;
    cin >> n;
    init(n);

    cin >> q;
    while (q--) {
        string s;
        cin >> s;

        Trie *cur = root;
        bool ans = false;
        for (char nxt : s) {
            while (cur != root) {
                bool flag = false;
                for (auto z : cur->go) {
                    if (nxt == z.fi) {
                        flag = true;
                        break;
                    }
                }
                if (flag)
                    break;

                cur = cur->fail;
            }
            for (auto z : cur->go) {
                if (nxt == z.fi) {
                    cur = z.se;
                    break;
                }
            }
            if (cur->output) {
                ans = true;
                break;
            }
        }
        cout << (ans ? "YES" : "NO") << '\n';
    }
}
