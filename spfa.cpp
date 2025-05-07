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

    vector<vector<pii>> graph(n + 1);
    for (int i = 0; i < m; i++) {
        int x, y, z;
        cin >> x >> y >> z;

        graph[x].push_back(make_pair(y, z));
    }

    vector<bool> in_dq(n + 1);
    vector<int> cnt(n + 1);
    vector<ll> dist(n + 1, LLONG_MAX);
    dist[1] = 0;

    deque<int> dq = {1};
    while (dq.sz) {
        int cur = dq.front();
        dq.pop_front();

        in_dq[cur] = false;

        if (++cnt[cur] == n) {
            cout << -1;
            return 0;
        }

        for (auto [nxt, d] : graph[cur]) {
            if (dist[nxt] > dist[cur] + d) {
                dist[nxt] = dist[cur] + d;

                if (!in_dq[nxt]) {
                    in_dq[nxt] = true;
                    dq.push_back(nxt);
                }
            }
        }
    }

    for (int i = 2; i <= n; i++)
        cout << (dist[i] == LLONG_MAX ? -1 : dist[i]) << '\n';
}
