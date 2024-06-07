// BOJ 2188 축사 배정

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

bool dfs(int cur, vector<int> &b, vector<bool> &vst, vector<vector<int>> &graph) {
    vst[cur] = true;

    for (int nxt : graph[cur]) {
        if (b[nxt] == 0 || (!vst[b[nxt]] && dfs(b[nxt], b, vst, graph))) {
            b[nxt] = cur;
            return true;
        }
    }

    return false;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> graph(n + 1);

    for (int i = 1; i <= n; i++) {
        int k;
        cin >> k;

        while (k--) {
            int x;
            cin >> x;

            graph[i].push_back(x);
        }
    }

    vector<int> b(m + 1);
    vector<bool> vst(n + 1);
    int ans = 0;

    for (int i = 1; i <= n; i++) {
        fill(vst.begin(), vst.end(), false);
        ans += dfs(i, b, vst, graph);
    }

    cout << ans;
}
