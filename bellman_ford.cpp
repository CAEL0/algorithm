# BOJ 11657 타임머신

#include <iostream>
#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;

const int MAX = 505;
const ll INF = 1e18;
ll V, E, D[MAX];
vector<pii> G[MAX];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> V >> E;
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        G[u].push_back(pii(v, w));
    }
    fill_n(D, MAX, INF);
    D[1] = 0;
    for (int i = 0; i < V - 1; i++)
        for (int u = 1; u <= V; u++)
            for (pii p: G[u])
                if (D[u] != INF)
                    D[p.fi] = min(D[p.fi], D[u] + p.se);
    
    for (int u = 1; u <= V; u++) {
        for (pii p: G[u]) {
            if (D[u] != INF && D[p.fi] > D[u] + p.se) {
                cout << -1;
                return 0;
            }
        }
    }
    for (int u = 2; u <= V; u++)
        cout << (D[u] == INF ? -1 : D[u]) << '\n';
}
