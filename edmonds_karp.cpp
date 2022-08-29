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

const int MAX = 405;
const int INF = 2e9;
const int S = MAX - 2;
const int E = MAX - 1;
int N, M, C[MAX][MAX], F[MAX][MAX];
vector<int> G[MAX];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        G[S].push_back(i);
        G[i].push_back(S);
        C[S][i] = 1;

        int tmp;
        cin >> tmp;
        while (tmp--) {
            int j;
            cin >> j;
            G[i].push_back(N + j);
            G[N + j].push_back(i);
            C[i][N + j] = 1;
        }
    }
    for (int j = N + 1; j <= N + M; j++) {
        G[j].push_back(E);
        G[E].push_back(j);
        C[j][E] = 1;
    }
    int ans = 0;
    while (1) {
        int prv[MAX];
        memset(prv, -1, sizeof(prv));
        queue<int> Q({S});
        while (Q.sz && prv[E] == -1) {
            int cur = Q.front();
            Q.pop();
            for (int nxt: G[cur]) {
                if (C[cur][nxt] > F[cur][nxt] && prv[nxt] == -1) {
                    prv[nxt] = cur;
                    Q.push(nxt);
                    if (nxt == E)
                        break;
                }
            }
        }
        if (prv[E] == -1)
            break;
        
        int flow = INF;
        int nxt = E;
        while (nxt != S) {
            int cur = prv[nxt];
            flow = min(flow, C[cur][nxt] - F[cur][nxt]);
            nxt = cur;
        }
        ans += flow;
        nxt = E;
        while (nxt != S) {
            int cur = prv[nxt];
            F[cur][nxt] += flow;
            F[nxt][cur] -= flow;
            nxt = cur;
        }
    }
    cout << ans;
}
