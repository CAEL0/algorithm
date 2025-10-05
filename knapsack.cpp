// BOJ 12865 평범한 배낭

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

    int n, k;
    cin >> n >> k;
    
    vector<int> w(n), v(n);
    for (int i = 0; i < n; i++)
        cin >> w[i] >> v[i];
    
    vector<vector<int>> dp(n, vector<int>(k + 1, 0));
    for (int j = 0; j <= k; j++)
        if (j >= w[0])
            dp[0][j] = v[0];
    
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < w[i]; j++)
            dp[i][j] = dp[i - 1][j];
        
        for (int j = w[i]; j <= k; j++)
            dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - w[i]] + v[i]);
    }
    
    cout << dp[n - 1][k];
}
