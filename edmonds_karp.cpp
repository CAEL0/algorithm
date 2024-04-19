// BOJ 2188 축사 배정

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

    int mx = n + m + 3;
    int start = mx - 2;
    int end = mx - 1;

    vector<vector<int>> graph(mx);
    vector<vector<int>> capacity(mx, vector<int>(mx, 0));
    vector<vector<int>> flow(mx, vector<int>(mx, 0));

    for (int i = 1; i <= n; i++) {
        graph[start].push_back(i);
        graph[i].push_back(start);
        capacity[start][i] = 1;

        int tmp;
        cin >> tmp;

        while (tmp--) {
            int j;
            cin >> j;

            graph[i].push_back(n + j);
            graph[n + j].push_back(i);
            capacity[i][n + j] = 1;
        }
    }

    for (int j = n + 1; j <= n + m; j++) {
        graph[j].push_back(end);
        graph[end].push_back(j);
        capacity[j][end] = 1;
    }

    int ans = 0;

    while (1) {
        vector<int> prv(mx, -1);
        deque<int> dq({start});

        while (dq.sz && prv[end] == -1) {
            int cur = dq.front();
            dq.pop_front();

            for (int nxt : graph[cur]) {
                if (capacity[cur][nxt] > flow[cur][nxt] && prv[nxt] == -1) {
                    prv[nxt] = cur;
                    dq.push_back(nxt);

                    if (nxt == end)
                        break;
                }
            }
        }

        if (prv[end] == -1)
            break;

        int f = INT_MAX;
        int nxt = end;

        while (nxt != start) {
            int cur = prv[nxt];
            f = min(f, capacity[cur][nxt] - flow[cur][nxt]);
            nxt = cur;
        }

        ans += f;
        nxt = end;

        while (nxt != start) {
            int cur = prv[nxt];
            flow[cur][nxt] += f;
            flow[nxt][cur] -= f;
            nxt = cur;
        }
    }
    cout << ans;
}
