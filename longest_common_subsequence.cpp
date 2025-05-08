// BOJ 9252 LCS 2

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

    string x, y;
    cin >> x >> y;

    int n = x.sz;
    int m = y.sz;

    vector<vector<int>> dp(n + 1, vector<int>(m + 1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (x[i - 1] == y[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    string ans;
    int i = n;
    int j = m;
    while (i > 0 && j > 0) {
        if (x[i - 1] == y[j - 1]) {
            ans += x[i - 1];
            i--;
            j--;
        } else if (dp[i][j] == dp[i - 1][j])
            i--;
        else
            j--;
    }

    reverse(ans.begin(), ans.end());

    cout << dp[n][m] << '\n' << ans;
}
