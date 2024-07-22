// BOJ 11438 LCA 2

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

struct LongestCommonAncestor {
    int n, k;
    vector<int> depth;
    vector<vector<int>> sparse;

    LongestCommonAncestor(int _n) {
        n = _n;
        k = ceil(log2(n)) + 1;

        depth.resize(n + 1);
        sparse.resize(k);
        for (int i = 0; i < k; i++)
            sparse[i].resize(n + 1);
    }

    void init(vector<vector<int>> &graph) {
        dfs(1, 1, graph);

        for (int i = 0; i < k - 1; i++)
            for (int j = 1; j <= n; j++)
                sparse[i + 1][j] = sparse[i][sparse[i][j]];
    }

    void dfs(int cur, int d, vector<vector<int>> &graph) {
        depth[cur] = d;

        for (int nxt : graph[cur]) {
            if (!depth[nxt]) {
                sparse[0][nxt] = cur;
                dfs(nxt, d + 1, graph);
            }
        }
    }

    int get(int a, int b) {
        if (depth[a] > depth[b])
            swap(a, b);

        int d = depth[b] - depth[a];
        for (int j = 0; j < k; j++)
            if (d & (1 << j))
                b = sparse[j][b];

        if (a == b)
            return a;

        while (1) {
            for (int j = k - 1; j >= 0; j--) {
                if (sparse[j][a] != sparse[j][b]) {
                    a = sparse[j][a];
                    b = sparse[j][b];
                }
            }

            if (sparse[0][a] == sparse[0][b])
                return sparse[0][a];
        }
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<vector<int>> graph(n + 1);
    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;

        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    LongestCommonAncestor lca(n);
    lca.init(graph);

    int q;
    cin >> q;

    while (q--) {
        int x, y;
        cin >> x >> y;

        cout << lca.get(x, y) << '\n';
    }
}
