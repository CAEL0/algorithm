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

struct Prim {
    int n;
    vector<vector<pll>> graph;

    Prim(int n, vector<vector<pll>> graph) : n(n), graph(graph) {}

    ll minimum_spanning_tree() {
        auto cmp = [](pll p, pll q) { return p.se > q.se; };
        priority_queue<pll, vector<pll>, decltype(cmp)> pq(cmp);

        vector<bool> vst(n + 1);
        vst[1] = true;

        ll ret = 0;
        int cur = 1;
        for (int i = 1; i < n; i++) {
            for (pll p : graph[cur])
                if (!vst[p.fi])
                    pq.push(p);

            while (1) {
                cur = pq.top().fi;
                ll d = pq.top().se;
                pq.pop();

                if (!vst[cur]) {
                    vst[cur] = true;
                    ret += d;
                    break;
                }
            }
        }

        return ret;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    vector<vector<pll>> graph(n + 1);
    for (int i = 0; i < m; i++) {
        ll x, y, z;
        cin >> x >> y >> z;

        graph[x].push_back(make_pair(y, z));
        graph[y].push_back(make_pair(x, z));
    }

    Prim prim(n, graph);

    cout << prim.minimum_spanning_tree();
}
