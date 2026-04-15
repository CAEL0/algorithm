// BOJ 11400 단절선

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

int dfs(int cur, int prv, int &idx, vector<vector<int>> &graph, vector<int> &vst, vector<pii> &ans) {
    vst[cur] = idx;
    int low = idx;
    idx++;

    for (int nxt : graph[cur]) {
        if (nxt == prv)
            continue;

        if (vst[nxt]) {
            low = min(low, vst[nxt]);
            continue;
        }

        int nxt_low = dfs(nxt, cur, idx, graph, vst, ans);
        low = min(low, nxt_low);

        if (vst[cur] < nxt_low)
            ans.push_back(make_pair(min(cur, nxt), max(cur, nxt)));
    }

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
        graph[y].push_back(x);
    }

    int idx = 1;
    vector<int> vst(n + 1);
    vector<pii> ans;
    dfs(1, 0, idx, graph, vst, ans);

    sort(ans.begin(), ans.end());

    cout << ans.sz << '\n';
    for (pii p : ans)
        cout << p.fi << ' ' << p.se << '\n';
}
