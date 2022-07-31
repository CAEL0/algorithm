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

ll N, K, M;
pll extended_gcd(ll x, ll y) {
    ll a0 = 1, a1 = 0, b0 = 0, b1 = 1, k;
    while (y) {
        k = x / y;
        swap(x, y);
        y %= x;
        swap(a0, a1);
        a1 -= k * a0;
        swap(b0, b1);
        b1 -= k * b0;
    }
    return pll(a0, b0);
}
ll combination(ll x, ll y, ll mod) {
    if (x < y)
        return 0;
    
    y = min(y, x - y);
    ll num = 1, den = 1;
    for (int i = 0; i < y; i++) {
        num = num * (x - i) % mod;
        den = den * (i + 1) % mod;
    }
    return (num * extended_gcd(den, mod).fi % mod + mod) % mod;
}
ll lucas(ll n, ll k, ll mod) {
    k = min(k, n - k);
    ll res = 1;
    while (k) {
        res = res * combination(n % mod, k % mod, mod) % mod;
        n /= mod;
        k /= mod;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> N >> K >> M;
    cout << lucas(N, K, M);
}
