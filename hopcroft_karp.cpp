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

const int MAX = 205;
const int INF = 2e9;
int N, M, A[MAX], B[MAX], lvl[MAX];
bool used[MAX];
vector<int> G[MAX];

bool dfs(int cur) {
    for (int nxt: G[cur]) {
        if (B[nxt] == -1 || lvl[B[nxt]] == lvl[cur] + 1 && dfs(B[nxt])) {
            used[cur] = true;
            A[cur] = nxt;
            B[nxt] = cur;
            return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        int s;
        cin >> s;
        while (s--) {
            int tmp;
            cin >> tmp;
            G[i].push_back(tmp);
        }
    }
    memset(A, -1, sizeof(A));
    memset(B, -1, sizeof(B));
    int ans = 0;
    while (1) {
        queue<int> Q;
        for (int i = 1; i <= N; i++) {
            if (!used[i]) {
                lvl[i] = 0;
                Q.push(i);
            } else
                lvl[i] = INF;
        }
        while (Q.sz) {
            int cur = Q.front();
            Q.pop();
            for (int nxt: G[cur]) {
                if (B[nxt] != -1 && lvl[B[nxt]] == INF) {
                    lvl[B[nxt]] = lvl[cur] + 1;
                    Q.push(B[nxt]);
                }
            }
        }
        int flow = 0;
        for (int i = 1; i <= N; i++)
            if (!used[i] && dfs(i))
                flow++;
        
        ans += flow;
        if (!flow)
            break;
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

const int MAX = 205;
const int INF = 2e9;
int N, M, A[MAX], B[MAX], lvl[MAX];
vector<int> G[MAX];

bool dfs(int cur) {
    for (int nxt: G[cur]) {
        if (lvl[B[nxt]] == lvl[cur] + 1 && (!B[nxt] || dfs(B[nxt]))) {
            A[cur] = nxt;
            B[nxt] = cur;
            return true;
        }
    }
    lvl[cur] = INF;
    return false;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        int s;
        cin >> s;
        while (s--) {
            int tmp;
            cin >> tmp;
            G[i].push_back(tmp);
        }
    }
    int ans = 0;
    while (1) {
        queue<int> Q;
        lvl[0] = INF;
        for (int i = 1; i <= N; i++) {
            if (!A[i]) {
                lvl[i] = 0;
                Q.push(i);
            } else
                lvl[i] = INF;
        }
        while (Q.sz) {
            int cur = Q.front();
            Q.pop();
            for (int nxt: G[cur]) {
                if (lvl[B[nxt]] == INF) {
                    lvl[B[nxt]] = lvl[cur] + 1;
                    Q.push(B[nxt]);
                }
            }
        }
        int flow = 0;
        for (int i = 1; i <= N; i++)
            if (!A[i] && dfs(i))
                flow++;
        
        ans += flow;
        if (!flow)
            break;
    }
    cout << ans;
}
