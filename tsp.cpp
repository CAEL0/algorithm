// BOJ 2098 외판원 순회

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

int f(int cur, int mask, int n, vector<vector<int>> &graph, vector<vector<int>> &dp) {
    if (dp[cur][mask] != -1)
        return dp[cur][mask];

    if (mask == (1 << n) - 1) {
        if (graph[cur][0])
            return dp[cur][mask] = graph[cur][0];
        return INT_MAX;
    }

    int ret = INT_MAX;

    for (int i = 0; i < n; i++) {
        if (!graph[cur][i] || mask & (1 << i))
            continue;

        int k = f(i, mask | (1 << i), n, graph, dp);
        if (k != INT_MAX)
            ret = min(ret, k + graph[cur][i]);
    }

    return dp[cur][mask] = ret;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<vector<int>> graph(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> graph[i][j];

    vector<vector<int>> dp(n, vector<int>(1 << n, -1));

    cout << f(0, 1, n, graph, dp);
}
