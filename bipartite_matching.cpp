// BOJ 11375 열혈강호

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

    BipartiteMatching(int n, int m) : n(n), m(m) {
        graph.resize(n + 1);
        b.resize(m + 1);
    }

    void add_edge(int x, int y) { graph[x].push_back(y); }

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

    BipartiteMatching bm(n, m);
    for (int i = 1; i <= n; i++) {
        int k;
        cin >> k;

        while (k--) {
            int x;
            cin >> x;

            bm.add_edge(i, x);
        }
    }

    cout << bm.maximum_matching();
}
