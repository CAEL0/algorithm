// BOJ 11438 LCA 2

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAX = 100005;

struct LCA {
    int n, depth[MAX], sparse[20][MAX];
    vector<int> graph[MAX];

    LCA(int n) { this->n = n; }

    void init() {
        for (int i = 1; i < n; i++) {
            int a, b;
            cin >> a >> b;
            graph[a].push_back(b);
            graph[b].push_back(a);
        }
        dfs(1, 1);

        for (int i = 0; i < 19; i++)
            for (int j = 1; j <= n; j++)
                sparse[i + 1][j] = sparse[i][sparse[i][j]];
    }

    void dfs(int cur, int d) {
        depth[cur] = d;
        for (int nxt : graph[cur]) {
            if (!depth[nxt]) {
                sparse[0][nxt] = cur;
                dfs(nxt, d + 1);
            }
        }
    }

    int get(int a, int b) {
        if (depth[a] > depth[b])
            swap(a, b);

        int d = depth[b] - depth[a];
        for (int j = 0; j < 20; j++)
            if (d & (1 << j))
                b = sparse[j][b];

        if (a == b)
            return a;

        while (1) {
            for (int j = 19; j >= 0; j--) {
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

    LCA lca = LCA(n);
    lca.init();

    int q;
    cin >> q;
    while (q--) {
        int a, b;
        cin >> a >> b;
        cout << lca.get(a, b) << '\n';
    }
}
