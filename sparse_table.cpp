// BOJ 17435 합성함수와 쿼리

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

    int n;
    cin >> n;

    vector<int> v(n);
    for (int i = 0; i < n; i++)
        cin >> v[i];

    vector<vector<int>> sparse(20, vector<int>(n + 1));
    for (int j = 0; j < n; j++)
        sparse[0][j + 1] = v[j];

    for (int i = 0; i < 19; i++)
        for (int j = 1; j <= n; j++)
            sparse[i + 1][j] = sparse[i][sparse[i][j]];

    int q;
    cin >> q;

    while (q--) {
        int m, x;
        cin >> m >> x;

        for (int i = 0; i < 20; i++)
            if (m & (1 << i))
                x = sparse[i][x];

        cout << x << '\n';
    }
}
