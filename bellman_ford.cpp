// BOJ 11657 타임머신

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    vector<vector<pll>> graph(n + 1);

    while (m--) {
        int u, v, w;
        cin >> u >> v >> w;

        graph[u].push_back({v, w});
    }

    vector<ll> dist(n + 1, LLONG_MAX);
    dist[1] = 0;

    for (int i = 1; i < n; i++)
        for (int cur = 1; cur <= n; cur++)
            for (pll &nxt : graph[cur])
                if (dist[cur] != LLONG_MAX)
                    dist[nxt.fi] = min(dist[nxt.fi], dist[cur] + nxt.se);

    for (int cur = 1; cur <= n; cur++) {
        for (pll &nxt : graph[cur]) {
            if (dist[cur] != LLONG_MAX && dist[nxt.fi] > dist[cur] + nxt.se) {
                cout << -1;
                return 0;
            }
        }
    }

    for (int i = 2; i <= n; i++)
        cout << (dist[i] == LLONG_MAX ? -1 : dist[i]) << '\n';
}
