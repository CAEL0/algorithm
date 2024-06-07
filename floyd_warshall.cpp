// BOJ 11404 플로이드

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    vector<vector<ll>> graph(n + 1, vector<ll>(n + 1, 1e18));

    for (int i = 1; i <= n; i++)
        graph[i][i] = 0;

    while (m--) {
        ll u, v, w;
        cin >> u >> v >> w;

        graph[u][v] = min(graph[u][v], w);
    }

    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            cout << (graph[i][j] == 1e18 ? 0 : graph[i][j]) << ' ';

        cout << '\n';
    }
}
