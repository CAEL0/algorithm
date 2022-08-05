// BOJ 9250 문자열 집합 판별

#include <iostream>
#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

int N, Q;
char P[105];
string S;

struct Trie {
    Trie* go[26];
    Trie* fail;
    bool output;

    Trie() {
        fill_n(go, 26, nullptr);
        output = false;
    }
    ~Trie() {
        for (int i = 0; i < 26; i++)
            if (go[i])
                delete go[i];
    }
    void insert(const char* s) {
        if (*s == '\0') {
            output = true;
            return;
        }
        int nxt = (*s - 'a');
        if (!go[nxt])
            go[nxt] = new Trie;
        
        go[nxt]->insert(s + 1);
    }
};
Trie* root;

void init() {
    root = new Trie;
    for (int i = 0; i < N; i++) {
        cin >> P;
        root->insert(P);
    }
    queue<Trie*> qu;
    root->fail = root;
    qu.push(root);
    while (qu.sz) {
        Trie* cur = qu.front();
        qu.pop();
        for (int i = 0; i < 26; i++) {
            Trie* nxt = cur->go[i];
            if (!nxt)
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
            
            qu.push(nxt);
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> N;
    init();
    
    cin >> Q;
    while (Q--) {
        cin >> S;

        Trie* cur = root;
        bool flag = false;
        for (int i = 0; i < S.length(); i++) {
            int nxt = S[i] - 'a';
            while (cur != root && !cur->go[nxt])
                cur = cur->fail;
            
            if (cur->go[nxt])
                cur = cur->go[nxt];
            
            if (cur->output) {
                flag = true;
                break;
            }
        }
        cout << (flag ? "YES" : "NO") << '\n';
    }
}
