// BOJ 2188 축사 배정

#include <iostream>
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
    cin.tie(0); cout.tie(0);

    int n, m, k;
    cin >> n >> m;
    k = n + m + 2;
    vector<int> graph[k];
    
    for (int j, tmp, i = 1; i < n + 1; i++) {
        graph[0].push_back(i);
        cin >> j;
        while (j--) {
            cin >> tmp;
            graph[i].push_back(n + tmp);
        }
    }
    for (int i = n + 1; i < k - 1; i++)
        graph[i].push_back(k - 1);

    int ans = 0;
    while (true) {
        int prev[k];
        fill_n(prev, k, -1);
        deque<int> dq;
        dq.push_back(0);
        while (!dq.empty()) {
            int cur = dq.front();
            dq.pop_front();
            for (int nxt : graph[cur]) {
                if (nxt == k - 1) {
                    prev[k - 1] = cur;
                    break;
                }
                if (prev[nxt] == -1) {
                    prev[nxt] = cur;
                    dq.push_back(nxt);
                }
            }
            if (prev[k - 1] != -1) break;
        }
        if (prev[k - 1] == -1) break;
        ans++;
        int nxt = k - 1;
        while (nxt) {
            int cur = prev[nxt];
            for (int i = 0; i < graph[cur].size(); i++) {
                if (graph[cur][i] == nxt) {
                    graph[cur].erase(graph[cur].begin() + i);
                    break;
                }
            }
            graph[nxt].push_back(cur);
            nxt = cur;
        }
    }
    cout << ans;
}

//--------------------------------------------------------------------------------

#include <iostream>
#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAX = 405;
const int INF = 2e9;
int N, M, K, prv[MAX], G[MAX][MAX];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> N >> M;
    K = N + M + 1;
    for (int i = 1; i <= N; i++) {
        G[0][i]++;
        int tmp;
        cin >> tmp;
        while (tmp--) {
            int j;
            cin >> j;
            G[i][N + j]++;
        }
    }
    for (int j = N + 1; j < K; j++)
        G[j][K]++;
    
    int ans = 0;
    while (1) {
        memset(prv, -1, sizeof(prv));
        deque<pii> dq;
        dq.push_back(pii(0, INF));
        int res = INF;
        while (dq.sz) {
            pii cur = dq.front();
            dq.pop_front();

            if (G[cur.fi][K]) {
                res = min(res, G[cur.fi][K]);
                prv[K] = cur.fi;
                break;
            }
            for (int nxt = 1; nxt < K; nxt++) {
                if (prv[nxt] == -1 && G[cur.fi][nxt]) {
                    prv[nxt] = cur.fi;
                    dq.push_back(pii(nxt, min(res, G[cur.fi][nxt])));
                }
            }
            if (prv[K] != -1)
                break;
        }
        if (prv[K] == -1)
            break;
        
        ans += res;
        int nxt = K;
        while (nxt) {
            int cur = prv[nxt];
            G[cur][nxt] -= res;
            G[nxt][cur] += res;
            nxt = cur;
        }
    }
    cout << ans;
}
