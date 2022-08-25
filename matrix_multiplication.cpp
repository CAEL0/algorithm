// BOJ 17401 일하는 세포

#include <iostream>
#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MOD = 1e9 + 7;
int T, N, D;

struct Matrix {
    int m[25][25] = {0};
    
    Matrix operator* (const Matrix o) const {
        Matrix res;
        for (int i = 0; i < 25; i++)
            for (int j = 0; j < 25; j++)
                for (int k = 0; k < 25; k++)
                    res.m[i][j] = (res.m[i][j] + (ll)m[i][k] * o.m[k][j]) % MOD;
        return res;
    }
} graph[105], MQ, MR, ans;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> T >> N >> D;
    for (int i = 0; i < T; i++) {
        int m;
        cin >> m;
        while (m--) {
            int a, b, c;
            cin >> a >> b >> c;
            graph[i].m[--a][--b] = c;
        }
    }
    int q = D / T;
    int r = D % T;
    for (int i = 0; i < N; i++)
        MQ.m[i][i] = MR.m[i][i] = ans.m[i][i] = 1;
    
    for (int i = 0; i < T; i++) {
        MQ = MQ * graph[i];
        if (i < r)
            MR = MR * graph[i];
    }
    while (q) {
        if (q & 1)
            ans = ans * MQ;
        
        q >>= 1;
        MQ = MQ * MQ;
    }
    ans = ans * MR;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << ans.m[i][j] << ' ';
        }
        cout << '\n';
    }
}
