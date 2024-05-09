// BOJ 10562 나이트

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MOD = 1e9 + 9;

ll ipow(ll base, ll exp) {
    ll ret = 1;

    while (exp) {
        if (exp & 1)
            ret = ret * base % MOD;

        base = base * base % MOD;
        exp >>= 1;
    }

    return ret;
}

vector<int> berlekamp_massey(vector<int> &x) {
    vector<int> ls, cur;
    int lf, ld;

    for (int i = 0; i < x.sz; i++) {
        ll t = 0;
        for (int j = 0; j < cur.sz; j++)
            t = (t + (ll)x[i - j - 1] * cur[j]) % MOD;

        if ((t - x[i]) % MOD == 0)
            continue;

        if (cur.empty()) {
            cur.resize(i + 1);
            lf = i;
            ld = (t - x[i]) % MOD;
            continue;
        }

        ll k = (t - x[i]) * ipow(ld, MOD - 2) % MOD;
        vector<int> c(i - lf - 1);
        c.push_back(k);

        for (auto &j : ls)
            c.push_back(-j * k % MOD);

        if (c.sz < cur.sz)
            c.resize(cur.sz);

        for (int j = 0; j < cur.sz; j++)
            c[j] = (c[j] + cur[j]) % MOD;

        if (i - lf + (int)ls.sz >= (int)cur.sz)
            tie(ls, lf, ld) = make_tuple(cur, i, (t - x[i]) % MOD);

        cur = c;
    }

    for (auto &i : cur)
        i = (i % MOD + MOD) % MOD;

    return cur;
}

int get_nth(vector<int> &rec, vector<int> &dp, ll n) {
    int m = rec.sz;
    vector<int> s(m), t(m);
    s[0] = 1;

    if (m != 1)
        t[1] = 1;
    else
        t[0] = rec[0];

    auto mul = [&rec](vector<int> v, vector<int> w) {
        int m = v.sz;
        vector<int> t(2 * m);

        for (int j = 0; j < m; j++) {
            for (int k = 0; k < m; k++) {
                t[j + k] += (ll)v[j] * w[k] % MOD;
                if (t[j + k] >= MOD)
                    t[j + k] -= MOD;
            }
        }

        for (int j = 2 * m - 1; j >= m; j--) {
            for (int k = 1; k <= m; k++) {
                t[j - k] += (ll)t[j] * rec[k - 1] % MOD;
                if (t[j - k] >= MOD)
                    t[j - k] -= MOD;
            }
        }

        t.resize(m);
        return t;
    };

    while (n) {
        if (n & 1)
            s = mul(s, t);

        t = mul(t, t);
        n >>= 1;
    }

    ll ret = 0;
    for (int i = 0; i < m; i++)
        ret = (ret + (ll)s[i] * dp[i] % MOD) % MOD;

    return ret;
}

int guess_nth_term(vector<int> &v, vector<int> &x, ll n) {
    if (n < x.sz)
        return x[n];

    return get_nth(v, x, n);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    vector<vector<vector<int>>> dp(5);
    for (int i = 2; i <= 4; i++) {
        dp[i].resize(105);
        int k = 1 << (2 * i);

        for (int n = 0; n < 105; n++)
            dp[i][n].resize(k);
    }

    for (int j = 0; j < 16; j++)
        dp[2][2][j] = 1;

    for (int n = 3; n < 100; n++) {
        for (int i = 0; i < 16; i++) {
            ll k = 0;

            for (int j = 0; j < 16; j++) {
                if ((i & 1) && (j & 8))
                    continue;

                if ((i & 2) && (j & 4))
                    continue;

                if (!(i & 4) != !(j & 1))
                    continue;

                if (!(i & 8) != !(j & 2))
                    continue;

                k += dp[2][n - 1][j];
            }

            dp[2][n][i] = k % MOD;
        }
    }

    for (int i = 0; i < 64; i++) {
        if ((i & 1) && (i & 32))
            continue;

        if ((i & 4) && (i & 8))
            continue;

        dp[3][2][i] = 1;
    }

    for (int n = 3; n < 100; n++) {
        for (int i = 0; i < 64; i++) {
            if ((i & 1) && (i & 32))
                continue;

            if ((i & 4) && (i & 8))
                continue;

            ll k = 0;
            for (int j = 0; j < 64; j++) {
                if ((i & 1) && (j & 16))
                    continue;

                if ((i & 2) && (j & 8))
                    continue;

                if ((i & 2) && (j & 32))
                    continue;

                if ((i & 4) && (j & 16))
                    continue;

                if ((i & 8) && (j & 32))
                    continue;

                if ((i & 32) && (j & 8))
                    continue;

                if (!(i & 8) != !(j & 1))
                    continue;

                if (!(i & 16) != !(j & 2))
                    continue;

                if (!(i & 32) != !(j & 4))
                    continue;

                k += dp[3][n - 1][j];
            }

            dp[3][n][i] = k % MOD;
        }
    }

    for (int i = 0; i < 256; i++) {
        if ((i & 1) && (i & 64))
            continue;

        if ((i & 2) && (i & 128))
            continue;

        if ((i & 4) && (i & 16))
            continue;

        if ((i & 8) && (i & 32))
            continue;

        dp[4][2][i] = 1;
    }

    for (int n = 3; n < 100; n++) {
        for (int i = 0; i < 256; i++) {
            if ((i & 1) && (i & 64))
                continue;

            if ((i & 2) && (i & 128))
                continue;

            if ((i & 4) && (i & 16))
                continue;

            if ((i & 8) && (i & 32))
                continue;

            ll k = 0;
            for (int j = 0; j < 256; j++) {
                if ((i & 1) && (j & 32))
                    continue;

                if ((i & 2) && (j & 16))
                    continue;

                if ((i & 2) && (j & 64))
                    continue;

                if ((i & 4) && (j & 32))
                    continue;

                if ((i & 4) && (j & 128))
                    continue;

                if ((i & 8) && (j & 64))
                    continue;

                if ((i & 16) && (j & 64))
                    continue;

                if ((i & 32) && (j & 128))
                    continue;

                if ((i & 64) && (j & 16))
                    continue;

                if ((i & 128) && (j & 32))
                    continue;

                if (!(i & 16) != !(j & 1))
                    continue;

                if (!(i & 32) != !(j & 2))
                    continue;

                if (!(i & 64) != !(j & 4))
                    continue;

                if (!(i & 128) != !(j & 8))
                    continue;

                k += dp[4][n - 1][j];
            }

            dp[4][n][i] = k % MOD;
        }
    }

    vector<vector<int>> v(5);

    for (int i = 2; i <= 4; i++) {
        v[i].push_back(1 << i);

        for (int n = 2; n < 100; n++) {
            ll k = 0;
            for (int j = 0; j < dp[i][n].sz; j++)
                k += dp[i][n][j];

            v[i].push_back(k % MOD);
        }
    }

    vector<vector<int>> bm(5);
    for (int i = 2; i <= 4; i++)
        bm[i] = berlekamp_massey(v[i]);

    int t;
    cin >> t;

    while (t--) {
        int m, n;
        cin >> m >> n;

        if (m == 1)
            cout << ipow(2, n) << '\n';
        else
            cout << get_nth(bm[m], v[m], n - 1) << '\n';
    }
}
