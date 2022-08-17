// BOJ 2150 Strongly Connected Component

#include <iostream>
#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second
 
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAX = 200005;
int N, M, T;
bool vst[MAX];
vector<int> stk, res;
vector<vector<int>> scc;
vector<int> graph[MAX], rev[MAX];

void dfs1(int cur) {
    for (int nxt: graph[cur]) {
        if (!vst[nxt]) {
            vst[nxt] = true;
            dfs1(nxt);
        }
    }
    stk.push_back(cur);
}
void dfs2(int cur) {
    for (int nxt: rev[cur]) {
        if (!vst[nxt]) {
            vst[nxt] = true;
            dfs2(nxt);
        }
    }
    res.push_back(cur);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
 
    cin >> N >> M;
    while (M--) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        rev[v].push_back(u);
    }
    for (int i = 1; i <= N; i++) {
        if (!vst[i]) {
            vst[i] = true;
            dfs1(i);
        }
    }
    memset(vst, false, sizeof(vst));
    while (stk.sz) {
        int i = stk.bk;
        stk.pop_back();
        if (!vst[i]) {
            vst[i] = true;
            res.clear();
            dfs2(i);
            scc.push_back(res);
        }
    }
    cout << scc.sz << '\n';
    for (auto &res: scc) {
        sort(res.begin(), res.end());
        res.push_back(-1);
    }
    sort(scc.begin(), scc.end());
    for (auto &res: scc) {
        for (int i: res)
            cout << i << ' ';
        cout << '\n';
    }
}
