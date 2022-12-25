// BOJ 11402 이항 계수 4

#include <iostream>
#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;

const int MAX = 2005;
ll N, K, MOD, fac[MAX], inv[MAX];

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

ll combination(ll n, ll k) {
    if (n < k)
        return 0;
    return fac[n] * inv[k] % MOD * inv[(n - k) % MOD] % MOD;
}

ll lucas(ll n, ll k) {
    k = min(k, n - k);
    ll ret = 1;
    while (k) {
        ret = ret * combination(n % MOD, k % MOD) % MOD;
        n /= MOD;
        k /= MOD;
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> N >> K >> MOD;

    fac[0] = 1;
    for (int i = 1; i < MOD; i++)
        fac[i] = fac[i - 1] * i % MOD;
    
    inv[MOD - 1] = ipow(fac[MOD - 1], MOD - 2);
    for (int i = MOD - 2; i >= 0; i--)
        inv[i] = inv[i + 1] * (i + 1) % MOD;

    cout << lucas(N, K);
}
