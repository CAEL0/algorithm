// BOJ 1199 오일러 회로

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
