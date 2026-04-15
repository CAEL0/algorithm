// BOJ 11266 단절점

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

int dfs(int cur, int idx, bool is_root, vector<vector<int>> &graph, vector<int> &vst, vector<int> &ans) {
    vst[cur] = idx;
    int low = idx;
    idx++;

    int cnt = 0;
    bool flag = true;
    for (int nxt : graph[cur]) {
        if (vst[nxt]) {
            low = min(low, vst[nxt]);
            continue;
        }

        cnt++;

        int nxt_low = dfs(nxt, idx, false, graph, vst, ans);
        low = min(low, nxt_low);

        if (!is_root && flag && vst[cur] <= nxt_low) {
            flag = false;
            ans.push_back(cur);
        }
    }

    if (is_root && cnt >= 2)
        ans.push_back(cur);

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

    vector<int> vst(n + 1);
    vector<int> ans;
    for (int x = 1; x <= n; x++) {
        if (vst[x] == 0) {
            int idx = 1;
            dfs(x, idx, true, graph, vst, ans);
        }
    }
    sort(ans.begin(), ans.end());

    cout << ans.sz << '\n';
    for (int x : ans)
        cout << x << ' ';
}
