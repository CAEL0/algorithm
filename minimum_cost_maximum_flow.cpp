// BOJ 11407 책 구매하기 3

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
    int source = mx - 2;
    int sink = mx - 1;
    vector<vector<int>> capacity(mx, vector<int>(mx));
    vector<vector<int>> cost(mx, vector<int>(mx));
    vector<vector<int>> flow(mx, vector<int>(mx));
    vector<vector<int>> graph(mx);

    for (int i = 1; i <= n; i++) {
        cin >> capacity[source][i];

        graph[source].push_back(i);
        graph[i].push_back(source);
    }

    for (int j = n + 1; j <= n + m; j++) {
        cin >> capacity[j][sink];

        graph[j].push_back(sink);
        graph[sink].push_back(j);
    }

    for (int j = n + 1; j <= n + m; j++) {
        for (int i = 1; i <= n; i++) {
            cin >> capacity[i][j];

            graph[i].push_back(j);
            graph[j].push_back(i);
        }
    }

    for (int j = n + 1; j <= n + m; j++) {
        for (int i = 1; i <= n; i++) {
            cin >> cost[i][j];

            cost[j][i] = -cost[i][j];
        }
    }

    int min_cost = 0;
    vector<int> prv(mx);
    vector<int> dist(mx);
    vector<bool> in_dq(mx);
    while (1) {
        fill(prv.begin(), prv.end(), -1);
        fill(dist.begin(), dist.end(), INT_MAX);
        fill(in_dq.begin(), in_dq.end(), false);

        deque<int> dq = {source};
        dist[source] = 0;
        in_dq[source] = true;

        while (dq.sz) {
            int cur = dq.front();
            dq.pop_front();

            in_dq[cur] = false;
            for (int nxt : graph[cur]) {
                if (capacity[cur][nxt] > flow[cur][nxt] && dist[nxt] > dist[cur] + cost[cur][nxt]) {
                    dist[nxt] = dist[cur] + cost[cur][nxt];
                    prv[nxt] = cur;
                    if (!in_dq[nxt]) {
                        in_dq[nxt] = true;
                        dq.push_back(nxt);
                    }
                }
            }
        }

        if (prv[sink] == -1)
            break;

        int f = INT_MAX;
        int nxt = sink;
        while (nxt != source) {
            int cur = prv[nxt];
            f = min(f, capacity[cur][nxt] - flow[cur][nxt]);
            nxt = cur;
        }

        nxt = sink;
        while (nxt != source) {
            int cur = prv[nxt];
            min_cost += f * cost[cur][nxt];
            flow[cur][nxt] += f;
            flow[nxt][cur] -= f;
            nxt = cur;
        }
    }

    int max_flow = 0;
    for (int i = 1; i <= n; i++)
        max_flow += flow[source][i];

    cout << max_flow << '\n' << min_cost;
}
