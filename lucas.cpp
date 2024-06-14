// BOJ 11402 이항 계수 4

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

ll ipow(ll base, ll exp, ll MOD) {
    ll ret = 1;
    while (exp) {
        if (exp & 1)
            ret = ret * base % MOD;
        exp >>= 1;
        base = base * base % MOD;
    }
    return ret;
}

ll inverse(ll x, ll MOD) { return ipow(x, MOD - 2, MOD); }

ll comb(ll n, ll k, vector<ll> &fac, vector<ll> &inv, ll MOD) {
    if (n < k)
        return 0;
    return fac[n] * inv[k] % MOD * inv[n - k] % MOD;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    ll n, k, MOD;
    cin >> n >> k >> MOD;

    k = min(k, n - k);

    vector<ll> fac(MOD);
    fac[0] = 1;

    for (int i = 1; i < MOD; i++)
        fac[i] = fac[i - 1] * i % MOD;

    vector<ll> inv(MOD);
    inv.bk = inverse(fac.bk, MOD);

    for (int i = MOD - 2; i >= 0; i--)
        inv[i] = inv[i + 1] * (i + 1) % MOD;

    ll ans = 1;

    while (k) {
        ans = ans * comb(n % MOD, k % MOD, fac, inv, MOD) % MOD;
        n /= MOD;
        k /= MOD;
    }

    cout << ans;
}
