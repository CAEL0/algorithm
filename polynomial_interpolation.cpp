// BOJ 27293 거듭제곱의 합 2

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MOD = 1e9 + 7;

ll ipow(ll base, ll exp) {
    ll ret = 1;
    while (exp) {
        if (exp & 1)
            ret = ret * base % MOD;

        exp >>= 1;
        base = base * base % MOD;
    }

    return ret;
}

ll f(int n, int k, vector<ll> &v, ll denominator) {
    if (n <= k + 5) {
        ll ret = 0;
        for (int i = 1; i <= n; i++)
            ret = (ret + ipow(i, k)) % MOD;

        return ret;
    }

    ll ret = 0;
    for (int i = 1; i <= k + 2; i++) {
        if (i > 1) {
            denominator = denominator * (MOD + 1 - i) % MOD;
            denominator = denominator * ipow(k + 3 - i, MOD - 2) % MOD;
        }

        ret = (ret + v[i] * ipow(denominator * (n - i) % MOD, MOD - 2) % MOD) % MOD;
    }

    for (int i = 1; i <= k + 2; i++)
        ret = ret * (n - i) % MOD;

    return ret;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int q;
    cin >> q;

    while (q--) {
        int a, b, k;
        cin >> a >> b >> k;

        if (b - a + 1 <= k + 5) {
            ll ans = 0;
            for (int i = a; i <= b; i++)
                ans = (ans + ipow(i, k)) % MOD;

            cout << ans << '\n';
            continue;
        }

        vector<ll> v(k + 3);
        for (int i = 1; i <= k + 2; i++)
            v[i] = (v[i - 1] + ipow(i, k)) % MOD;

        ll denominator = 1;
        for (int i = 1; i <= k + 1; i++)
            denominator = denominator * (MOD - i) % MOD;

        cout << (f(b, k, v, denominator) - f(a - 1, k, v, denominator) + MOD) % MOD << '\n';
    }
}
