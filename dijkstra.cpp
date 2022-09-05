// BOJ 1753 최단경로

#include <iostream>
#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second
 
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAX = 20005;
int V, E, S, dist[MAX];
struct Node {
    int x, d;
    bool operator<(const Node &o) const {
        return d > o.d;
    }
};
vector<pii> G[MAX];

void dijkstra() {
    priority_queue<Node> pq;
    pq.push({S, 0});
    while (pq.sz) {
        Node cur = pq.top();
        pq.pop();
        if (dist[cur.x] == cur.d) {
            for (pii nxt: G[cur.x]) {
                if (cur.d + nxt.se < dist[nxt.fi]) {
                    dist[nxt.fi] = cur.d + nxt.se;
                    pq.push({nxt.fi, dist[nxt.fi]});
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> V >> E >> S;
    while (E--) {
        int a, b, c;
        cin >> a >> b >> c;
        G[a].push_back(pii(b, c));
    }
    fill_n(dist, V + 1, 2e9);
    dist[S] = 0;
    dijkstra();
    for (int i = 1; i <= V; i++) {
        if (dist[i] == 2e9)
            cout << "INF" << '\n';
        else
            cout << dist[i] << '\n';
    }
}
