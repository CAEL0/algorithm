# BOJ 12865 평범한 배낭

#include <iostream>
#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

int N, K, W[105], V[105], dp[105][100005];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> N >> K;
    for (int i = 1; i <= N; i++)
        cin >> W[i] >> V[i];
    
    for (int i = 1; i <= N; i++) {
        for (int w = 1; w <= K; w++) {
            if (W[i] > w)
                dp[i][w] = dp[i - 1][w];
            else
                dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - W[i]] + V[i]);
        }
    }
    cout << dp[N][K];
}
