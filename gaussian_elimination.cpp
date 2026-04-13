// BOJ 22940 선형 연립 방정식

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

    vector<vector<ll>> v(n + 1, vector<ll>(n + 2));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n + 1; j++)
            cin >> v[i][j];

    for (int i = 1; i <= n; i++) {
        for (int ii = i + 1; ii <= n; ii++) {
            ll k = v[ii][i];
            for (int j = i; j <= n + 1; j++)
                v[ii][j] *= v[i][i];

            for (int j = i; j <= n + 1; j++)
                v[ii][j] -= k * v[i][j];

            ll g = v[ii][i];
            for (int j = i + 1; j <= n + 1; j++)
                g = gcd(g, v[ii][j]);

            for (int j = i; j <= n + 1; j++)
                v[ii][j] /= g;
        }
    }

    for (int i = n; i >= 1; i--) {
        for (int j = n + 1; j >= i; j--)
            v[i][j] /= v[i][i];

        for (int ii = i - 1; ii >= 1; ii--) {
            v[ii][n + 1] -= v[ii][i] * v[i][n + 1];
            v[ii][i] = 0;
        }
    }

    for (int i = 1; i <= n; i++)
        cout << v[i][n + 1] << ' ';
}
