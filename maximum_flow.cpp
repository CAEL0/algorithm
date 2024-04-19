// BOJ 1014 컨닝

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

bool dfs(int cur, vector<vector<int>> &graph, vector<int> &a, vector<int> &b, vector<bool> &vst) {
    vst[cur] = true;

    for (int nxt : graph[cur]) {
        if (b[nxt] == -1 || (!vst[b[nxt]] && dfs(b[nxt], graph, a, b, vst))) {
            a[cur] = nxt;
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

    vector<int> dx = {1, 1, 0, 0, -1, -1};
    vector<int> dy = {-1, 1, -1, 1, -1, 1};

    int t;
    cin >> t;

    while (t--) {
        int n, m;
        cin >> n >> m;

        vector<string> v(n);
        for (int i = 0; i < n; i++)
            cin >> v[i];

        int k = n * m;
        int ans = k;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (v[i][j] != '.')
                    ans--;

        vector<vector<int>> graph(k);

        for (int i = 0; i < n; i++) {
            for (int j = 1; j < m; j += 2) {
                if (v[i][j] != '.')
                    continue;

                for (int d = 0; d < 6; d++) {
                    int x = i + dx[d];
                    int y = j + dy[d];

                    if (0 <= min(x, y) && x < n && y < m && v[x][y] == '.')
                        graph[n * j + i].push_back(n * y + x);
                }
            }
        }

        vector<int> a(k, -1);
        vector<int> b(k, -1);
        vector<bool> vst(k);

        for (int i = 0; i < n; i++) {
            for (int j = 1; j < m; j += 2) {
                fill(vst.begin(), vst.end(), false);
                ans -= dfs(n * j + i, graph, a, b, vst);
            }
        }

        cout << ans << '\n';
    }
}
