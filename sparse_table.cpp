// BOJ 17435

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n;
    cin >> n;

    int arr[n];
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    
    int sparse[20][n + 1];
    for (int j = 0; j < n; j++)
        sparse[0][j + 1] = arr[j];
    
    for (int i = 0; i < 19; i++)
        for (int j = 1; j <= n; j++)
            sparse[i + 1][j] = sparse[i][sparse[i][j]];

    int q, m, x;
    cin >> q;
    while (q--) {
        cin >> m >> x;
        for (int i = 0; i < 20; i++) {
            if (m & (1 << i))
                x = sparse[i][x];
        }
        cout << x << '\n';
    }
}
