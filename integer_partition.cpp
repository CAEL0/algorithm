#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MOD = 998244353;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    int m = max(2, (int)sqrt(n));

    vector<int> ans(n + 1);
    ans[0] = 1;

    vector<vector<int>> p(2, vector<int>(n + 1));

    for (int b = 1; b < m; b++) {
        int idx = b & 1;
        p[0][0] = (b == 1);

        for (int a = 1; a <= n; a++) {
            p[idx][a] = p[idx ^ 1][a - 1];

            if (a - b >= 0)
                p[idx][a] = (p[idx][a] + p[idx][a - b]) % MOD;

            ans[a] = (ans[a] + p[idx][a]) % MOD;
        }
    }

    vector<vector<int>> d(2, vector<int>(n + 1));

    for (int a = m; a >= 0; a--) {
        int idx = a & 1;

        for (int b = m; b <= n; b++) {
            d[idx][b] = (d[idx ^ 1][b - m] + p[(m - 1) & 1][b - 1]) % MOD;

            if (b - a - 1 >= m)
                d[idx][b] = (d[idx][b] + d[idx][b - a - 1]) % MOD;

            if (a == 0)
                ans[b] = (ans[b] + d[idx][b]) % MOD;
        }
    }

    for (int i = 0; i <= n; i++)
        cout << ans[i] << ' ';
}
