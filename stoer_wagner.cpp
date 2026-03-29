// BOJ 13367 Weeping Fig

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

struct StoerWagner {
    int n;
    vector<bool> merged;
    vector<vector<int>> graph;

    StoerWagner(int n, vector<vector<int>> graph) : n(n), graph(graph) { merged.resize(n + 1); }

    int minimum_cut() {
        int ret = INT_MAX;
        for (int i = 1; i < n; i++)
            ret = min(ret, minimum_cut_phase());

        return ret;
    }

    int minimum_cut_phase() {
        int ret = 0;
        int x = 0;
        int y = 0;
        vector<bool> used(n + 1);
        vector<int> dist(n + 1);
        while (1) {
            int mx = -1;
            int idx = 0;
            for (int i = 1; i <= n; i++) {
                if (merged[i] || used[i])
                    continue;

                if (mx < dist[i]) {
                    mx = dist[i];
                    idx = i;
                }
            }
            if (idx == 0)
                break;

            ret = mx;
            x = y;
            y = idx;
            used[idx] = true;

            for (int i = 1; i <= n; i++)
                if (!merged[i] && !used[i])
                    dist[i] += graph[i][idx];
        }

        merged[y] = true;
        for (int i = 1; i <= n; i++) {
            if (!merged[i]) {
                graph[x][i] += graph[y][i];
                graph[i][x] += graph[i][y];
            }
        }

        return ret;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;

    while (t--) {
        int n, m;
        cin >> n >> m;

        vector<vector<int>> graph(n + 1, vector<int>(n + 1));
        while (m--) {
            int x, y, z;
            cin >> x >> y >> z;

            graph[x][y] += z;
            graph[y][x] += z;
        }

        StoerWagner sw(n, graph);

        cout << sw.minimum_cut() << '\n';
    }
}
