// BOJ 7577 탐사

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

    vector<pair<pii, int>> edges(2 * n + 2 * m);
    for (int i = 0; i < n; i++) {
        edges[2 * i] = make_pair(make_pair(i, i + 1), 1);
        edges[2 * i + 1] = make_pair(make_pair(i + 1, i), 0);
    }

    for (int i = 0; i < m; i++) {
        int x, y, z;
        cin >> x >> y >> z;

        edges[2 * n + 2 * i] = make_pair(make_pair(x - 1, y), z);
        edges[2 * n + 2 * i + 1] = make_pair(make_pair(y, x - 1), -z);
    }

    vector<ll> dist(n + 1, LLONG_MAX);
    dist[0] = 0;
    for (int j = 0; j < n; j++)
        for (int i = 0; i < edges.sz; i++)
            if (dist[edges[i].fi.fi] != LLONG_MAX)
                dist[edges[i].fi.se] = min(dist[edges[i].fi.se], dist[edges[i].fi.fi] + edges[i].se);

    for (int i = 0; i < edges.sz; i++) {
        if (dist[edges[i].fi.fi] == LLONG_MAX)
            continue;

        if (dist[edges[i].fi.se] > dist[edges[i].fi.fi] + edges[i].se) {
            cout << "NONE";
            return 0;
        }
    }

    for (int i = n; i >= 1; i--)
        dist[i] -= dist[i - 1];

    for (int i = 1; i <= n; i++)
        cout << (dist[i] == 1 ? '#' : '-');
}
