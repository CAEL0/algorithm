// BOJ 1199 오일러 회로

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

void dfs(int cur, vector<int> &edges, vector<vector<int>> &graph, vector<bool> &used) {
    while (graph[cur].sz) {
        int idx = graph[cur].bk;
        graph[cur].pop_back();

        if (used[idx])
            continue;

        used[idx] = true;
        int nxt = edges[idx] ^ cur;

        dfs(nxt, edges, graph, used);
    }

    cout << cur << ' ';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<int> edges;
    vector<vector<int>> graph(n + 1);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int x;
            cin >> x;

            if (i > j)
                continue;

            while (x--) {
                graph[i].push_back(edges.sz);
                graph[j].push_back(edges.sz);
                edges.push_back(i ^ j);
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        if (graph[i].sz & 1) {
            cout << -1;
            return 0;
        }
    }

    vector<bool> used(edges.sz);
    dfs(1, edges, graph, used);
}

//--------------------------------------------------------------------------------

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

void dfs(int cur, vector<vector<int>> &graph) {
    for (int nxt = 1; nxt < graph.sz; nxt++) {
        int k = 0;

        while (graph[cur][nxt] > 2) {
            graph[cur][nxt] -= 2;
            graph[nxt][cur] -= 2;
            k++;
        }

        if (graph[cur][nxt]) {
            graph[cur][nxt]--;
            graph[nxt][cur]--;

            dfs(nxt, graph);

            cout << nxt << ' ';

            while (k--)
                cout << cur << ' ' << nxt << ' ';
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<vector<int>> graph(n + 1, vector<int>(n + 1));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cin >> graph[i][j];

    for (int i = 1; i <= n; i++) {
        int degree = 0;

        for (int j = 1; j <= n; j++)
            degree += graph[i][j];

        if (degree & 1) {
            cout << -1;
            return 0;
        }
    }

    dfs(1, graph);

    cout << 1;
}
