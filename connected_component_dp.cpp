// BOJ 13188 Kangaroo

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MOD = 1e9 + 7;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, s, e;
    cin >> n >> s >> e;

    vector<vector<ll>> dp(n + 1, vector<ll>(n + 1));
    dp[0][0] = 1;
    int k = 0;
    for (int i = 1; i <= n; i++) {
        if (i == s) {
            k++;
            for (int j = 0; j <= i - 1; j++) {
                dp[i][j + 1] = (dp[i][j + 1] + dp[i - 1][j]) % MOD;
                dp[i][j] = (dp[i][j] + dp[i - 1][j]) % MOD;
            }
        } else if (i == e) {
            k++;
            for (int j = 0; j <= i - 1; j++) {
                dp[i][j + 1] = (dp[i][j + 1] + dp[i - 1][j]) % MOD;
                dp[i][j] = (dp[i][j] + dp[i - 1][j]) % MOD;
            }
        } else {
            for (int j = 0; j <= i - 1; j++)
                dp[i][j + 1] = (dp[i][j + 1] + dp[i - 1][j] * (j + 1 - k) % MOD) % MOD;

            for (int j = 2; j <= i - 1; j++)
                dp[i][j - 1] = (dp[i][j - 1] + dp[i - 1][j] * (j - 1) % MOD) % MOD;
        }
    }

    cout << dp[n][1];
}
