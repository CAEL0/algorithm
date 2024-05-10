// BOJ 2150 Strongly Connected Component

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

int dfs(int cur, int &idx, vector<int> &v, vector<int> &vst, vector<bool> &finish, vector<vector<int>> &graph, vector<vector<int>> &scc) {
    v.push_back(cur);
    vst[cur] = idx;
    int low = idx++;

    for (int nxt : graph[cur]) {
        if (!vst[nxt])
            low = min(low, dfs(nxt, idx, v, vst, finish, graph, scc));
        else if (!finish[nxt])
            low = min(low, vst[nxt]);
    }

    if (low != vst[cur])
        return low;

    vector<int> w;
    while (1) {
        int top = v.bk;
        v.pop_back();

        finish[top] = true;
        w.push_back(top);

        if (cur == top)
            break;
    }

    scc.push_back(w);
    return low;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> graph(n + 1);

    while (m--) {
        int x, y;
        cin >> x >> y;

        graph[x].push_back(y);
    }

    int idx = 1;
    vector<int> v, vst(n + 1);
    vector<bool> finish(n + 1);
    vector<vector<int>> scc;

    for (int i = 1; i <= n; i++)
        if (!vst[i])
            dfs(i, idx, v, vst, finish, graph, scc);

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
