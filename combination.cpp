// BOJ 11401 이항 계수 3

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

vector<ll> get_fac(int n) {
    vector<ll> fac(n + 1);
    fac[0] = 1;
    for (int i = 1; i <= n; i++)
        fac[i] = fac[i - 1] * i % MOD;

    return fac;
}

vector<ll> get_inv(int n, vector<ll> &fac) {
    vector<ll> inv(n + 1);
    inv[n] = ipow(fac[n], MOD - 2);
    for (int i = n - 1; i >= 0; i--)
        inv[i] = inv[i + 1] * (i + 1) % MOD;

    return inv;
}

ll comb(int n, int k, vector<ll> &fac, vector<ll> &inv) {
    if (k < 0 || n < k)
        return 0;

    return fac[n] * inv[k] % MOD * inv[n - k] % MOD;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, k;
    cin >> n >> k;

    vector<ll> fac = get_fac(n);
    vector<ll> inv = get_inv(n, fac);

    cout << comb(n, k, fac, inv);
}
