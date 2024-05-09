// BOJ 1753 최단경로

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

struct Node {
    int x, d;
    bool operator<(const Node &o) const { return d > o.d; }
};

vector<int> dijkstra(int start, vector<vector<pii>> &graph) {
    vector<int> dist(graph.sz, INT_MAX);
    dist[start] = 0;

    priority_queue<Node> pq;
    pq.push({start, 0});

    while (pq.sz) {
        Node cur = pq.top();
        pq.pop();

        if (dist[cur.x] != cur.d)
            continue;

        for (pii &nxt : graph[cur.x]) {
            if (cur.d + nxt.se < dist[nxt.fi]) {
                dist[nxt.fi] = cur.d + nxt.se;
                pq.push({nxt.fi, dist[nxt.fi]});
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

    vector<vector<pii>> graph(n + 1);
    
    while (m--) {
        int u, v, w;
        cin >> u >> v >> w;

        graph[u].push_back(pii(v, w));
    }

    vector<int> dist = dijkstra(start, graph);

    for (int i = 1; i <= n; i++) {
        if (dist[i] == INT_MAX)
            cout << "INF" << '\n';
        else
            cout << dist[i] << '\n';
    }
}
