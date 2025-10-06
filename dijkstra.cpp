// BOJ 1753 최단경로

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

vector<ll> dijkstra(int start, vector<vector<pll>> &graph) {
    vector<ll> dist(graph.sz, LLONG_MAX);
    dist[start] = 0;

    priority_queue<pll, vector<pll>, greater<pll>> pq;
    pq.push(make_pair(0, start));

    while (pq.sz) {
        auto [d, cur] = pq.top();
        pq.pop();

        if (dist[cur] != d)
            continue;

        for (auto [nxt, dd] : graph[cur]) {
            if (dist[nxt] > d + dd) {
                dist[nxt] = d + dd;
                pq.push(make_pair(dist[nxt], nxt));
            }
        }
    }

    return dist;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m, start;
    cin >> n >> m >> start;

    vector<vector<pll>> graph(n + 1);
    while (m--) {
        ll x, y, z;
        cin >> x >> y >> z;

        graph[x].push_back(make_pair(y, z));
    }

    vector<ll> dist = dijkstra(start, graph);
    for (int i = 1; i <= n; i++) {
        if (dist[i] == LLONG_MAX)
            cout << "INF" << '\n';
        else
            cout << dist[i] << '\n';
    }
}
