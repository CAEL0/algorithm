// BOJ 7045 Tree Cutting

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

int dfs(int cur, int prv, vector<vector<int>> &graph, vector<int> &parent, vector<int> &sub) {
    parent[cur] = prv;
    sub[cur]++;

    for (int nxt : graph[cur])
        if (nxt != prv)
            sub[cur] += dfs(nxt, cur, graph, parent, sub);

    return sub[cur];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<vector<int>> graph(n + 1);
    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;

        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    vector<int> parent(n + 1);
    vector<int> sub(n + 1);
    dfs(1, 0, graph, parent, sub);

    vector<int> ans;
    int cur = 1;

    while (cur) {
        int total = 1;
        int mx = 0;
        int idx = 0;

        for (int nxt : graph[cur]) {
            if (nxt == parent[cur])
                continue;

            total += sub[nxt];
            if (mx < sub[nxt]) {
                mx = sub[nxt];
                idx = nxt;
            }
        }

        if (n - total > n / 2)
            break;

        if (mx <= n / 2)
            ans.push_back(cur);

        cur = idx;
    }

    sort(ans.begin(), ans.end());
    for (int x : ans)
        cout << x << '\n';
}
