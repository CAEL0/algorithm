// BOJ 1197 최소 스패닝 트리

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
    for (int i = 0; i < m; i++) {
        ll u, v, w;
        cin >> u >> v >> w;

        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    auto cmp = [](pll &p, pll &q) { return p.se > q.se; };
    priority_queue<pll, vector<pll>, decltype(cmp)> pq(cmp);

    vector<bool> vst(n + 1);
    vst[1] = true;

    ll ans = 0;
    int cur = 1;

    for (int i = 1; i < n; i++) {
        for (pll &edge : graph[cur])
            if (!vst[edge.fi])
                pq.push(edge);

        while (1) {
            pll edge = pq.top();
            pq.pop();

            if (!vst[edge.fi]) {
                cur = edge.fi;
                vst[cur] = true;
                ans += edge.se;
                break;
            }
        }
    }

    cout << ans;
}
