// BOJ 17401 일하는 세포

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MOD = 1e9 + 7;

struct Matrix {
    int n;
    vector<vector<int>> v;

    Matrix(int _n) {
        n = _n;
        v.resize(n);

        for (int i = 0; i < n; i++)
            v[i].resize(n);
    }

    Matrix operator*(const Matrix &o) const {
        Matrix ret(n);

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                for (int k = 0; k < n; k++)
                    ret.v[i][j] = (ret.v[i][j] + (ll)v[i][k] * o.v[k][j]) % MOD;

        return ret;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t, n, d;
    cin >> t >> n >> d;

    vector<Matrix> graph(t, Matrix(n));

    for (int i = 0; i < t; i++) {
        int m;
        cin >> m;

        while (m--) {
            int a, b, c;
            cin >> a >> b >> c;

            graph[i].v[--a][--b] = c;
        }
    }

    int q = d / t;
    int r = d % t;

    Matrix x(n), y(n), ans(n);

    for (int i = 0; i < n; i++)
        x.v[i][i] = y.v[i][i] = ans.v[i][i] = 1;

    for (int i = 0; i < t; i++) {
        x = x * graph[i];
        if (i < r)
            y = y * graph[i];
    }

    while (q) {
        if (q & 1)
            ans = ans * x;

        q >>= 1;
        x = x * x;
    }

    ans = ans * y;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << ans.v[i][j] << ' ';

        cout << '\n';
    }
}
