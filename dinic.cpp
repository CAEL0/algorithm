// BOJ 13161 분단의 슬픔

#include <iostream>
#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAX = 505;
const int INF = 2e9;
const int S = MAX - 2;
const int E = MAX - 1;
int N, A[MAX], C[MAX][MAX], F[MAX][MAX], lvl[MAX], work[MAX];
vector<int> G[MAX];
bool vst[MAX];

int dfs(int cur, int flow) {
    if (cur == E)
        return flow;
    
    for (int &i = work[cur]; i < G[cur].sz; i++) {
        int nxt = G[cur][i];
        if (C[cur][nxt] > F[cur][nxt] && lvl[nxt] == lvl[cur] + 1) {
            int res = dfs(nxt, min(C[cur][nxt] - F[cur][nxt], flow));
            if (res > 0) {
                F[cur][nxt] += res;
                F[nxt][cur] -= res;
                return res;
            }
        }
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> A[i];
        if (A[i] == 1) {
            G[S].push_back(i);
            G[i].push_back(S);
            C[S][i] = INF;
        } else if (A[i] == 2) {
            G[i].push_back(E);
            G[E].push_back(i);
            C[i][E] = INF;
        }
    }
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> C[i][j];
            if (i != j) {
                G[i].push_back(j);
                G[j].push_back(i);
            }
        }
    }
    int ans = 0;
    while (1) {
        memset(lvl, -1, sizeof(lvl));
        lvl[S] = 0;
        queue<int> Q({S});
        while (Q.sz) {
            int cur = Q.front();
            Q.pop();
            for (int nxt: G[cur]) {
                if (C[cur][nxt] > F[cur][nxt] && lvl[nxt] == -1) {
                    lvl[nxt] = lvl[cur] + 1;
                    Q.push(nxt);
                }
            }
        }
        if (lvl[E] == -1)
            break;
        
        memset(work, 0, sizeof(work));
        while (1) {
            int flow = dfs(S, INF);
            ans += flow;
            if (!flow)
                break;
        }
    }
    queue<int> Q({S});
    while (Q.sz) {
        int cur = Q.front();
        Q.pop();
        for (int nxt: G[cur]) {
            if (C[cur][nxt] > F[cur][nxt] && !vst[nxt]) {
                vst[nxt] = true;
                Q.push(nxt);
            }
        }
    }
    cout << ans << '\n';
    for (int i = 1; i <= N; i++)
        if (vst[i])
            cout << i << ' ';
    cout << '\n';
    for (int i = 1; i <= N; i++)
        if (!vst[i])
            cout << i << ' ';
    cout << '\n';
}
