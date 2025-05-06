// BOJ 11657 타임머신

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

    vector<pair<pii, ll>> edges(m);
    for (int i = 0; i < m; i++)
        cin >> edges[i].fi.fi >> edges[i].fi.se >> edges[i].se;

    vector<ll> dist(n + 1, LLONG_MAX);
    dist[1] = 0;
    for (int j = 1; j < n; j++)
        for (int i = 0; i < m; i++)
            if (dist[edges[i].fi.fi] != LLONG_MAX)
                dist[edges[i].fi.se] = min(dist[edges[i].fi.se], dist[edges[i].fi.fi] + edges[i].se);

    for (int i = 0; i < m; i++) {
        if (dist[edges[i].fi.fi] == LLONG_MAX)
            continue;

        if (dist[edges[i].fi.se] > dist[edges[i].fi.fi] + edges[i].se) {
            cout << -1;
            return 0;
        }
    }

    for (int i = 2; i <= n; i++)
        cout << (dist[i] == LLONG_MAX ? -1 : dist[i]) << '\n';
}
