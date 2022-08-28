// BOJ 11407 책 구매하기 3

#include <iostream>
#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAX = 205;
const int INF = 2e9;
const int S = MAX - 2;
const int E = MAX - 1;
int N, M, C[MAX][MAX], D[MAX][MAX], F[MAX][MAX];
vector<int> G[MAX];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        cin >> C[S][i];
        G[S].push_back(i);
        G[i].push_back(S);
    }
    for (int j = N + 1; j <= N + M; j++) {
        cin >> C[j][E];
        G[j].push_back(E);
        G[E].push_back(j);
    }
    for (int j = N + 1; j <= N + M; j++) {
        for (int i = 1; i <= N; i++) {
            cin >> C[i][j];
            G[i].push_back(j);
            G[j].push_back(i);
        }
    }
    for (int j = N + 1; j <= N + M; j++) {
        for (int i = 1; i <= N; i++) {
            cin >> D[i][j];
            D[j][i] = -D[i][j];
        }
    }
    int ans1 = 0;
    int ans2 = 0;
    while (1) {
        int res[MAX], prv[MAX];
        bool isin[MAX];
        fill_n(res, MAX, INF);
        memset(prv, -1, sizeof(prv));
        memset(isin, false, sizeof(isin));
        res[S] = 0;
        isin[S] = true;
        queue<int> Q;
        Q.push(S);
        while (Q.sz) {
            int cur = Q.front();
            Q.pop();
            isin[cur] = false;

            for (int nxt: G[cur]) {
                if (C[cur][nxt] > F[cur][nxt] && res[nxt] > res[cur] + D[cur][nxt]) {
                    res[nxt] = res[cur] + D[cur][nxt];
                    prv[nxt] = cur;
                    if (!isin[nxt]) {
                        isin[nxt] = true;
                        Q.push(nxt);
                    }
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
        nxt = E;
        while (nxt != S) {
            int cur = prv[nxt];
            ans2 += flow * D[cur][nxt];
            F[cur][nxt] += flow;
            F[nxt][cur] -= flow;
            nxt = cur;
        }
    }
    for (int i = 1; i <= N; i++)
        ans1 += F[S][i];
    
    cout << ans1 << '\n' << ans2;
}
