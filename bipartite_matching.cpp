// BOJ 2188 축사 배정

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

struct BipartiteMatching {
    int n, m;
    vector<int> b;
    vector<vector<int>> graph;

    BipartiteMatching(int n, int m, vector<vector<int>> &graph) : n(n), m(m), graph(graph) { b.resize(m + 1); }

    int maximum_matching() {
        int ret = 0;
        vector<bool> vst(n + 1);
        for (int i = 1; i <= n; i++) {
            fill(vst.begin(), vst.end(), false);
            if (dfs(i, vst))
                ret++;
        }

        return ret;
    }

    bool dfs(int cur, vector<bool> &vst) {
        vst[cur] = true;

        for (int nxt : graph[cur]) {
            if (b[nxt] == 0 || (!vst[b[nxt]] && dfs(b[nxt], vst))) {
                b[nxt] = cur;
                return true;
            }
        }

        return false;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> graph(n + 1);
    for (int i = 1; i <= n; i++) {
        int k;
        cin >> k;

        while (k--) {
            int x;
            cin >> x;

            graph[i].push_back(x);
        }
    }

    BipartiteMatching bm(n, m, graph);

    cout << bm.maximum_matching();
}
