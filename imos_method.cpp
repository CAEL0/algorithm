// BOJ 5541 釘 (Nails)

#include <iostream>
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int N, M, imos[5005][5005];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> N >> M;
    while (M--) {
        int a, b, x;
        cin >> a >> b >> x;

        imos[a][b]++;
        imos[a][b + 1]--;
        imos[a + x + 1][b]--;
        imos[a + x + 2][b + 1]++;
        imos[a + x + 1][b + x + 2]++;
        imos[a + x + 2][b + x + 2]--;
    }
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            imos[i][j] += imos[i][j - 1];
    
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            imos[i][j] += imos[i - 1][j];

    for (int k = 2; k <= 2 * N; k++) {
        for (int i = max(1, k - N); i <= min(N, k - 1); i++) {
            int j = k - i;
            imos[i][j] += imos[i - 1][j - 1];
        }
    }
    int ans = 0;
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            ans += (imos[i][j] > 0);
    
    cout << ans;
}
