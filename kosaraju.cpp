// BOJ 2150 Strongly Connected Component

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

void dfs1(int cur, vector<int> &v, vector<bool> &vst, vector<vector<int>> &graph) {
    for (int nxt : graph[cur]) {
        if (!vst[nxt]) {
            vst[nxt] = true;
            dfs1(nxt, v, vst, graph);
        }
    }

    v.push_back(cur);
}

void dfs2(int cur, vector<int> &w, vector<bool> &vst, vector<vector<int>> &reversed) {
    for (int nxt : reversed[cur]) {
        if (!vst[nxt]) {
            vst[nxt] = true;
            dfs2(nxt, w, vst, reversed);
        }
    }

    w.push_back(cur);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> graph(n + 1), reversed(n + 1);

    while (m--) {
        int x, y;
        cin >> x >> y;

        graph[x].push_back(y);
        reversed[y].push_back(x);
    }

    vector<int> v;
    vector<bool> vst(n + 1);

    for (int i = 1; i <= n; i++) {
        if (!vst[i]) {
            vst[i] = true;
            dfs1(i, v, vst, graph);
        }
    }

    vector<int> w;
    vector<vector<int>> scc;
    fill(vst.begin(), vst.end(), false);

    while (v.sz) {
        int i = v.bk;
        v.pop_back();

        if (!vst[i]) {
            vst[i] = true;

            w.clear();
            dfs2(i, w, vst, reversed);
            scc.push_back(w);
        }
    }

    for (auto &w : scc)
        sort(w.begin(), w.end());

    sort(scc.begin(), scc.end());

    cout << scc.sz << '\n';
    for (auto &w : scc) {
        for (int x : w)
            cout << x << ' ';
        cout << -1 << '\n';
    }
}
